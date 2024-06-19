# include "../include/CGI.hpp"

CGI::CGI(void){}

CGI::~CGI(void){}


std::string _append_index(Client &client)
{
	// if not directory -> return;
	struct stat s;
	if (access(client.request->_path.c_str(), F_OK) != 0 || client.location->autoIndex) // ???
		return (client.request->_path);
	if (stat(client.request->_path.c_str(),&s) == 0)
	{
		if(s.st_mode & S_IFREG) // if it's file
		{
			std::cout << "it is a file" << std::endl;
			return (client.request->_path);
		}
		else if (s.st_mode & S_IFDIR) 
		{
			std::cout << "it is a dir" << std::endl;
			if (client.request->_path[client.request->_path.size() - 1] != '/')
				client.request->_path += "/";
			// loop index
			std::string tmp_file;
			std::cout << "hello1 index size: " << client.location->index.size() << std::endl;
			for (int i = 0; i < client.location->index.size(); i++)
			{
				tmp_file = client.request->_path + client.location->index[i];
				std::cout << "tmp_file: " << tmp_file << std::endl; 
				if (access(tmp_file.c_str(), F_OK) == 0){
					std::cout << "found index!!: " << tmp_file << std::endl;  
					return (tmp_file);
				}
			}
			return (client.request->_path);
		} 
		return (client.request->_path);

	}
	return (client.request->_path);
}

t_cgi_return CGI::rout(Client &client, Server &server)
{
	t_cgi_return ret;

	client.location = _select_location(*client.request, server);
	if (!client.location)
		std::cout << RED << "can't find matching location" << RESET << std::endl;
	if (false /* plaeaseee */ && !_is_allow_method(client.request->_method, *client.location)) {
		if (client.request->_method == HEAD)
			return (t_cgi_return){HEAD, 403};
		return (t_cgi_return){STATUS_CODE, 403};
	}
	if (client.location->ret.have){
		// redirect
		client.request->_path = client.location->ret.text;
		return ((t_cgi_return){STATUS_CODE, client.location->ret.code});
	}
	if (client.request->_method == DELETE){
		return (t_cgi_return){DELETE, 0};	
	}
	client.request->_path = client.location->root + client.request->_path; // prepend root path
	client.request->_path = _append_index(client);	// append index
	std::cout << YEL << "after find index:" << client.request->_path << RESET << std::endl;

	// check access
	if (access(client.request->_path.c_str(), F_OK) != 0 || is_directory(client.request->_path))
		return ((t_cgi_return){STATUS_CODE, 404});

	// check auto index
	if (client.location->autoIndex && is_directory(client.request->_path)){
		return ((t_cgi_return){AUTO_INDEX, 0});
	}
	if (client.location->cgiPass) { // <=============== HELLO PTEW
		// cgi
		pipe(client.pipe_fd);
		pipe(client.pipe_fd_out);
		client.pipe_available = true;

		client.child_pid = fork();
		if (client.child_pid == 0){ // child
			dup2(client.pipe_fd[0], STDIN_FILENO);
			dup2(client.pipe_fd_out[1], STDOUT_FILENO);
			// 
			close(client.pipe_fd[0]);
			close(client.pipe_fd[1]);
			close(client.pipe_fd_out[0]);
			close(client.pipe_fd_out[1]);
			char *arg[] = {(char *)client.request->_path.c_str(), NULL};
			execve((char *)client.request->_path.c_str(), arg, NULL);
			exit(0);
		}
		else{ // perent
			write(client.pipe_fd[1], client.request->_body.c_str(), client.request->_body.size());
			return ((t_cgi_return){FORKING, 0}); // return write able fd
		}
	}
	return ((t_cgi_return){STATUS_CODE, 200});

}

size_t read_line(int fd, char* buffer)
{
    char char_buf;
    size_t buffer_size = 0;
    while (read(fd, &char_buf, 1) > 0 && char_buf != '\n')
        buffer[buffer_size++] = char_buf;
    buffer[buffer_size] = '\0';

    return buffer_size;
}


Response& CGI::readfile(Client &client, Server &server, t_cgi_return cgi_return)
{
	Response response;
	bool	readable = false;
	char buffer[BUFFERSIZE];
	int fd;
	int length = 0;

	std::cout << "in readfile" << std::endl; 
	if (cgi_return.type == STATUS_CODE && cgi_return.status_code >= 400)
	{
		// check in error list and read error file
		// client.request->_path = "docs/error.html"; // need fix to error in server
		response = server.errorPage(cgi_return.status_code);
		readable = false;
	} 
	else if (cgi_return.type == STATUS_CODE && cgi_return.status_code >= 100) 
	{
		std::cout << "read file: " << client.request->_path << std::endl;
		fd = open(client.request->_path.c_str(), O_RDONLY);
		readable = true;
	}
	else if (cgi_return.type == FORKING)
	{
		std::cout << "read cgi" << std::endl;
		fd = client.pipe_fd_out[0];
		close(client.pipe_fd[0]);
		close(client.pipe_fd[1]);
		close(client.pipe_fd_out[1]);
		readable = true;
	}
	else if (cgi_return.type == AUTO_INDEX)
	{
		// return
		// response = _auto_indexing(client, server); 
		readable = false;
	}
	else if (cgi_return.type == DELETE)
	{
		response = _delete_method(client);
		readable = false;
	}
	else if (cgi_return.type == HEAD)
	{
		
	}

	std::cout << "fd: " << fd << std::endl;
	int read_byte = 0;
	while (readable)
	{
		bzero(buffer, length);
		length = read(fd, buffer, BUFFERSIZE - 1);
		buffer[length] = '\0';
		if (length <= 0)
			break;
		response._body.append(buffer, length);
	}
	if (cgi_return.type == STATUS_CODE)
		response._return_code = cgi_return.status_code;
	else 
		response._return_code = 0;
	response._content_type = _mime.get_mime_type(client.request->_path);
	response.genarate_header();
	return (response);
}

int		_delete_method(Client &client)
{

}
		
bool CGI::_is_path(std::string path)
{
	if (path[path.size() - 1] == '/')
		return (true);
	return (false);
}

std::string CGI::_get_only_path(std::string path)
{
	std::size_t found;
	std::string str;

	found = path.find_last_of("/\\");
	str = path.substr(0, found);
	return (str);
}

Location* CGI::_compare_location(std::string str, std::map<std::string, Location> &conf)
{
	std::map<std::string, Location>::iterator it;

	for (it = conf.begin(); it != conf.end(); it++){
		if (it->first == str){
			std::cout << "checked with " << it->first  << std::endl;
			return (&(it->second));
		}
	}
	std::cout << "not match any location" << std::endl;
	return (NULL);
}

Location* CGI::_select_location(Request &request, Server &server)
{
	bool match = false;
	Location *select_loc;
	struct stat s;
	

	std::cout << YEL << "request path: " << request._path << RESET << std::endl;
	if ((select_loc = _compare_location(request._path, server._config)) != NULL)
		match = true;
	std::string only_path = _get_only_path(request._path);
	std::cout << "only_path: " << only_path << std::endl;
	while (!match){
		if ((select_loc = _compare_location(only_path, server._config)) != NULL){
			std::cout << YEL << "config match!" << RESET << std::endl;
			match = true;
		}
		else
			only_path = _get_only_path(only_path);
		if (only_path == ""){
			std::cout << "get / location" << std::endl;
			select_loc = &server._config["/"];
			break;
		}

	}
	return (select_loc);
}

bool	CGI::_is_allow_method(t_method method, Location &location)
{
	for (int i = 0; i < location.allowMethod.size(); i++){
		if (method == location.allowMethod[i])
			return (true);
	}
	return (false);
}

std::ostream& operator <<(std::ostream &os, const t_res_type &res_type)
{
	switch (res_type)
	{
		case STATUS_CODE:
			os << "STATUS_CODE";
			break;
		case FORKING:
			os << "FORKING";
			break;
		case DELETE:
			os << "DELETE";
			break;
		case AUTO_INDEX:
			os << "AUTO_INDEX";	
			break;
		case HEAD:
			os << "HEAD";	
			break;
		default:
			os << "Undefind response type";
			break;
	}
	return (os);
}

std::ostream& operator <<(std::ostream &os, const t_cgi_return &cgi_ret)
{
	os << "Resposne Type: " << cgi_ret.type;
	if (cgi_ret.type == STATUS_CODE)
		os << ":: " << cgi_ret.status_code << std::endl;
	return (os);
}