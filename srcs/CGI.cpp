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
			for (int i = 0; i < client.location->index.size(); i++)
			{
				tmp_file = client.request->_path + client.location->index[i];
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
	client.request->_path = concat_path(client.location->root, client.request->_path);
	if (!_is_allow_method(client.request->_method, *client.location)) {
		std::cout << YEL << client.request->_method << " method is not allow" << RESET << std::endl; 
		if (client.request->_method == HEAD)
			return (t_cgi_return){HEAD_RES, 403};
		return (t_cgi_return){STATUS_CODE_RES, 403};
	}
	if (client.location->ret.code){ // here
		// redirect
		std::cout << "redirect" << std::endl;
		client.request->_path = client.location->ret.text;
		return ((t_cgi_return){STATUS_CODE_RES, client.location->ret.code});
	}
	if (client.request->_method == DELETE){
		return (t_cgi_return){DELETE_RES, 0};	
	}
	if (!is_directory(client.request->_path) || client.location->autoIndex == false){ // if not autoindex
		client.request->_path = _append_index(client);	// append index
		// check access
		std::cout << YEL << "after find index:" << client.request->_path << RESET << std::endl;
		if (access(client.request->_path.c_str(), F_OK) != 0 || is_directory(client.request->_path))
			return ((t_cgi_return){STATUS_CODE_RES, 404});

	} else 
		return ((t_cgi_return){AUTO_INDEX_RES, 0});

	std::string msg;

	if (client.request->_method == GET)
		msg = client.request->_query_string;
	else if (client.request->_method == POST)
		msg = client.request->_body;
	else
		msg = std::string("unknown method");
	if (client.location->cgiPass) { // <=============== HELLO PTEW
		// cgi
		pipe(client.pipe_fd);
		pipe(client.pipe_fd_out);
		client.pipe_available = true;

		client.child_pid = fork();
		if (client.child_pid == 0){ // child
			dup2(client.pipe_fd[0], STDIN_FILENO);
			dup2(client.pipe_fd_out[1], STDOUT_FILENO);
			close(client.pipe_fd[0]);
			close(client.pipe_fd[1]);
			close(client.pipe_fd_out[0]);
			close(client.pipe_fd_out[1]);

			std::string query_string = "QUERY_STRING=" + client.request->_query_string;
			std::string content_length = "CONTENT_LENGTH=" + client.request->getHeaderFieldMap()["Content-Length"];
			std::string content_type = "CONTENT_TYPE=" + client.request->getHeaderFieldMap()["Content-Type"];
			std::string request_method = "REQUEST_METHOD=";
			if (client.request->_method == POST)
				request_method += "POST";
			else if (client.request->_method == GET)
				request_method += "GET";
			
			char *envp[] = {
            (char*)request_method.c_str(),
            (char*)content_length.c_str(),
            (char*)content_type.c_str(),
			(char*)query_string.c_str(),
            nullptr
        	};

			std::cerr << BLU << "execute file: " << client.request->_path.c_str() << RESET << std::endl ;
			char *arg[2] = {(char *)client.request->_path.c_str(), nullptr};
			if (execve(arg[0], arg, envp) != 0)
				perror("execve");
			exit(1);
		}
		else{ // perent
			std::cout << BLU << "msg: " << msg << RESET << std::endl;
			write(client.pipe_fd[1], msg.c_str(), msg.size());
			return ((t_cgi_return){FORKING_RES, 0}); // return write able fd
		}
	}
	return ((t_cgi_return){STATUS_CODE_RES, 200});

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


Response* CGI::readfile(Client &client, Server &server, t_cgi_return cgi_return)
{
	Response *response = new Response;
	bool	readable = false;
	char buffer[BUFFERSIZE];
	int fd;
	int length = 0;

	std::cout << "in readfile" << std::endl; 
	if (cgi_return.type == STATUS_CODE_RES && cgi_return.status_code >= 400)
	{
		std::cout << "error page" << std::endl;
		if (server.errorPage(cgi_return.status_code, *response))
			std::cout << BLU << "error page from resource" << RESET << std::endl;
		else 
			std::cout << BLU << "no error page for this status code (" << cgi_return.status_code << ")" << RESET << std::endl;
		readable = false;
	} 
	else if (cgi_return.type == STATUS_CODE_RES && cgi_return.status_code >= 100) 
	{
		std::cout << "read file: " << client.request->_path << std::endl;
		fd = open(client.request->_path.c_str(), O_RDONLY);
		readable = true;
		if (fd <= 0){
			if (server.errorPage(404, *response))
				std::cout << BLU << "error page from resource" << RESET << std::endl;
			else 
				std::cout << BLU << "no error page for this status code (404)" << RESET << std::endl;
			readable = false;
		}
	}
	else if (cgi_return.type == FORKING_RES)
	{
		std::cout << "read cgi" << std::endl;
		response->cgiPass = true;
		response->_return_code = 200;
		fd = client.pipe_fd_out[0];
		close(client.pipe_fd[0]);
		close(client.pipe_fd[1]);
		close(client.pipe_fd_out[1]);
		readable = true;
	}
	else if (cgi_return.type == AUTO_INDEX_RES)
	{
		// return
		_auto_indexing(client, server, *response);  // here
		readable = false;
	}
	else if (cgi_return.type == DELETE_RES)
	{
		_delete_method(client, *response); // here 
		readable = false;
	}
	else if (cgi_return.type == HEAD_RES)
	{
		response->_return_code = 304;
		response->_body = "";
		readable = false;
	}

	std::cout << "fd: " << fd << std::endl;
	while (readable)
	{
		bzero(buffer, length);
		length = read(fd, buffer, BUFFERSIZE - 1);
		buffer[length] = '\0';
		if (length <= 0){
			close(fd);
			break;
		}
		response->_body.append(buffer, length);
	}
	if (cgi_return.type == STATUS_CODE_RES)
		response->_return_code = cgi_return.status_code;
	if (readable && client.location->cgiPass != true)
		response->_content_type = _mime.get_mime_type(client.request->_path);
	std::cout << std::boolalpha << response->cgiPass << std::endl;
	return (response);
}

bool	CGI::_auto_indexing(Client &client, Server &server, Response &response)
{
	DIR *dr;
	struct dirent *en;
	dr = opendir(client.request->_path.c_str());
	if (!dr)
		std::cerr << RED << "Cannot open " << client.request->_path << " directory (in auto indexing)" << RESET << std::endl;

	response._body += "<!DOCTYPE html>\n";
	response._body += "<html lang=\"en\">\n";
	response._body += "<head>\n";
	response._body += "<meta charset=\"UTF-8\">\n";
	response._body += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
	response._body += "<title>";
	response._body += client.request->_path; 
	response._body += "</title>\n";
	response._body += "</head>\n";
	response._body += "<body>\n";
	response._body += "<h1>\n";
	response._body += "index of ";
	response._body += client.request->_path;
	response._body += "</h1>\n";
	response._body += "<hr>\n";
	while ((en = readdir(dr)) != NULL){
		std::string filename(en->d_name);
		std::string url;
		std::cout << "filename: " << filename << std::endl;
		if (filename == ".") {
			url = "#";
		}
		if (filename == "..") {
			// dont forget
		}
		else {
			url = concat_path(client.request->_path, filename);
		}
		replace_str(url, client.location->root, " ");
		trimSpaces(url);
		url = "/" + url;
		response._body += "<a href=\"";
		response._body += url;
		response._body += "\">";
		response._body += filename;
		response._body += "</a>\n";
		response._body += "<br>\n";
	}
	closedir(dr);
	response._body += "</body>\n";
	response._body += "</html>\n";
	response._content_type = "text/html";
	response._return_code = 200;
	
	return (true);
}

bool	CGI::_delete_method(Client &client, Response &response)
{

	std::cout << "delete file: " << client.request->_path << std::endl;
	if (access(client.request->_path.c_str(), F_OK) != 0){
		client.server->errorPage(404, response);
		return (false);
	}
	if (remove(client.request->_path.c_str()) != 0){
		client.server->errorPage(500, response);
		return (false);
	}
	response._return_code = 200;
	return (true);
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
			std::cout << "match config " << it->first  << std::endl;
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
	

	std::cout << RED << "request path: " << request._path << RESET << std::endl;
	std::cout << RED << "request path size: " << request._path.size() << RESET << std::endl;
	if ((select_loc = _compare_location(request._path, server._config)) != NULL)
		match = true;
	std::string only_path = _get_only_path(request._path);
	while (!match){
		if ((select_loc = _compare_location(only_path, server._config)) != NULL){
			std::cout << YEL << "config match!" << RESET << std::endl;
			match = true;
		}
		else
			only_path = _get_only_path(only_path);
		if (only_path.size() <= 1){
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
	if (res_type == STATUS_CODE_RES)
		os << "STATUS_CODE";
	else if (res_type == FORKING_RES)
		os << "FORKING";
	else if (res_type == DELETE_RES)
		os << "DELETE";
	else if (res_type == AUTO_INDEX_RES)
		os << "AUTO_INDEX";	
	else if (res_type == HEAD_RES)
		os << "HEAD";	
	else
		os << "Undefind response type";
	return (os);
}

std::ostream& operator <<(std::ostream &os, const t_cgi_return &cgi_ret)
{
	os << "Resposne Type: " << cgi_ret.type;
	if (cgi_ret.type == STATUS_CODE_RES)
		os << ":: " << cgi_ret.status_code << std::endl;
	return (os);
}
