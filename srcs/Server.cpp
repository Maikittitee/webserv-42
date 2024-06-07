#include "../include/Server.hpp"

Server::Server(void)
{
	name = "localhost"; //? server_name
	ipAddr = "0.0.0.0"; //? listen could be ip address or port
	port = 80;

}

Server::Server(int port, char **env){
	if (port < 0 || port > 65535)
		throw PortNotExist();
	else
	_env = env;
}

Server::~Server (void) {
	close(_server_fd);
}


void Server::send_response(const char *response, int client_fd)
{
	send(client_fd, response, strlen(response), 0);
}

char *Server::PortNotExist::what() const throw(){
	return ((char *)"Your port is not in range of 0 - 65535");
}
std::string Server::errorPage(int error_code)
{
	std::string body;

	switch (error_code){
		case 404:
			readFile(body, "docs/error.html");
		case 405:
			readFile(body, "docs/error.html");
	}
	return (body);
}

std::string Server::do_cgi(Request &request)
{
	int fd[2];
	int pid;

	pipe(fd);

	pid = fork();
	if (pid == 0){
		char **arg = (char **)malloc(sizeof(char *) * 3);
		arg[0] = (char *)request._path.c_str();
		arg[1] = (char *)request._query_string.c_str();
		arg[2] = NULL;
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[0]);
		execve(arg[0], arg, _env);
	}
	// waitpid(pid ,NULL, NULL);
	dup2(fd[0], STDIN_FILENO);
	close(fd[1]);
	close(fd[0]);

	char buffer[1024];
	read(STDIN_FILENO, buffer, 1024);	
	return (std::string(buffer));
}

std::string Server::rout(Request &request)
{
	Response response;

	// // find config;
	// std::cout << "bp1" << std::endl;
	// Location target_location = select_location(request);	
	// std::cout << "bp2" << std::endl;

	// // 	หา config location ของ request (ถ้าไม่มีส่ง default config ไป)
	// // send request and target config to response;
	// response.receive_request(request, target_location);
	// if (response._return_code >= 400) // incase error => redirect to error file
	// 	response.set_body(errorPage(response._return_code));
	// if (response._return_code < 0) {// incase cgi => redirect to do cgi
	// 	response._return_code = 200;
	// 	response.cgiPass = true;
	// 	response.set_body(do_cgi(request));
	// }
	response.set_body(response.get_body_from_file("docs/test.html"));
	response.genarate_header();
	return (response.get_response_text());	
}

static std::vector<std::string> get_keys(std::map<std::string, Location> map)
{
	std::vector<std::string> ret;
	std::map<std::string, Location>::const_iterator iter;
	while (iter != map.end()){
		ret.insert(ret.end(), iter->first);
		iter++;
	}
	return (ret);
}

static int get_match_length(std::string target, std::string src)
{
	int cnt = 0;
	int i = 0;
	while (i < target.size() && i < src.size()){
		if (target[i] == src[i])
			cnt += 1;
		else
			return (cnt);
		i++;
	}
	return (cnt);

}

Location& Server::select_location(Request &request)
{
	std::string target_path = request._path;
	std::cout << "bp3" << std::endl;
	std::vector<std::string> rout_paths;
	std::cout << "bp4" << std::endl;
	std::map<std::string, Location>::const_iterator it;
	for (it = _config.begin(); it != _config.end(); it++)
	{
		std::cout << it->first << std::endl;
		std::cout << it->second << std::endl;
	}
	rout_paths = get_keys(_config);
	std::cout << "bp5" << std::endl;
	std::vector<int> acc_length;
	
	int	i = 0;
	while (i < rout_paths.size()){
		acc_length.insert(acc_length.end(), get_match_length(target_path, rout_paths[i]));
		i++;
		std::cout << i << std::endl;
	}
	std::cout << "bp7" << std::endl;
	// auto index = std::max_element(acc_length.begin(), acc_length.end()) - acc_length.begin();
	// if (rout_paths[index].size() > acc_length[index])
	// 	return (_config["/"]);
	// std::cout << "rout of  " << request._path << " is " << rout_paths[index]  << std::endl; 
	// return (_config[rout_paths[index]]);
	return (_config["/"]);
}

std::ostream &operator<<(std::ostream &os, std::map<std::string, Location>map)
{
	std::map<std::string, Location>::const_iterator it;
	for (it = map.begin(); it != map.end(); it++)
	{
		os << it->first << std::endl;
		os << it->second << std::endl;
	}
	return (os);
}