#ifndef WS_UTILS_HPP
# define WS_UTILS_HPP

typedef enum e_method{
			ELSE,
			GET,
			POST,
			DELETE,
			HEAD,
} t_method;

typedef enum e_version{
	HTTP09, // HTTP/0.9
	HTTP10, // HTTP/1.0
	HTTP11, // HTTP/1.1
	HTTP00, // else
} t_version;

#endif
