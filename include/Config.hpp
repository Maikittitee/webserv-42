#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "Common.hpp"
# include "Server.hpp"

// NEED FIX

std::ostream& operator<<(std::ostream& os, const Location& location);
short   ft_stos(std::string str);
uint64_t        ft_stouint(std::string str);
void    ft_print_vec_str(std::vector<std::string> vec);
void    ft_print_vec_uint(std::vector<uint64_t> vec);
std::vector<std::string>    ft_split(std::string str);
std::string     ft_trim(std::string line, char c);
bool    ft_check_extension(char *file);
std::string     ft_getvalue(std::string key, std::string line);
std::string ft_getkey(std::string sp_line);
std::string     ft_trim_ispace(std::string line);
short   ft_getlocate(Location &location, std::string key, std::string value);
void    ft_prt_server(Server &sv);
void    ft_prt_allowmethod(std::map<std::string, Location>::iterator it, std::vector<t_method> allowMethod);
void    ft_prt_only_location(Location lc);
void    ft_prt_location(std::map<std::string, Location> _config); 
int     ft_stoi(std::string str);
void ft_prt_locate(short locate);
bool ft_check_name(std::string key);
bool    ft_check_sameport(std::vector<Server> sv);
void    ft_init_server(Server &server);
std::vector<t_method>   ft_get_allowMethod(std::string value);
void    ft_get_default_config(Location &def_loc, std::string key, std::string value);
int ft_checkfile(int ac, char *av);
int     ft_checktxt(std::string key, std::string value);
int     ft_cnt_paren(std::string key, std::string value);
void    ft_getlisten(int &stage, std::string value, std::vector<u_int64_t> &tmp_port);
int     parsing_config(int ac, char **av, std::vector<Server> &sv);

# endif