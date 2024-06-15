# include "../include/CGI.hpp"

CGI::CGI(void){}

CGI::~CGI(void){}


std::string _append_index(Client &client)
{
	// if not directory -> return;
	struct stat s;
	if (access(client.request->_path.c_str(), F_OK) != 0 || client.location->autoIndex)
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

int CGI::rout(Client &client, Server &server)
{
	client.location = _select_location(*client.request, server);
	if (!client.location)
		std::cout << RED << "can't find matching location" << RESET << std::endl;
	if (false /* plaeaseee */ && !_is_allow_method(client.request->_method, *client.location)) {
		return (403);
		//method not allow 
	}
	if (client.location->ret.have){
		// redirect
		client.request->_path = client.location->ret.text;
		return (client.location->ret.code);
	}
	if (client.request->_method == DELETE){
		// delete file 
	}
	client.request->_path = client.location->root + client.request->_path;
	client.request->_path = _append_index(client);
	std::cout << YEL << "after find index:" << client.request->_path << RESET << std::endl;
	// check access
	if (access(client.request->_path.c_str(), F_OK) != 0 || is_directory(client.request->_path))
		return (404);
	if (client.location->autoIndex && is_directory(client.request->_path)){
		return (1000);
	}
	if (client.location->cgiPass) { // <=============== HELLO PTEW
		// cgi
		pipe(client.pipe_fd);
		client.pipe_available = true;

		client.child_pid = fork();
		if (client.child_pid == 0){ // child
			dup2(client.pipe_fd[0], STDIN_FILENO);
			dup2(client.pipe_fd[1], STDOUT_FILENO);
			// 
			std::cout << "Hello From child proceass" << std::endl;
			exit(0);
		}
		return (client.pipe_fd[1]); // return write able fd
	}
	return (200);

}

std::string CGI::readfile(Client &client, Server &server, int return_code)
{
	Response response;
	char buffer[BUFFERSIZE];
	int fd;
	int length;

	if (return_code >= 400)
	{
		// check in error list and read error file
		client.request->_path = "docs/error.html"; // need fix to error in server
	}
	if (return_code >= 100) {
		std::cout << "read file: " << client.request->_path << std::endl;
		fd = open(client.request->_path.c_str(), O_RDONLY);
	}
	else {
		fd = client.pipe_fd[0];
	}
	std::cout << "fd: " << fd << std::endl;

	length = read(fd, buffer, BUFFERSIZE);
	while (length > 0)
	{
		response._body.append(buffer, length);
		length = read(fd, buffer, BUFFERSIZE);
	}
	response._return_code = return_code;
	response._content_type = _mime.get_mime_type(client.request->_path);
	response.genarate_header();
	return (response.get_response_text());
	

}
		
std::string CGI::readfile(int fd) // fd of child (cgi) process <=============== HELLOOOOO PTEW
{
	// อ่าน fd ของ child process แล้วเก็๋บไว้ใน buffer 
	// response.body = buffer
	// genate_header()
	// return (response txt)
	// close fd
	return ("READFILE FROM FD");
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