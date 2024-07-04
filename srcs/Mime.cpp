#include "../include/Mime.hpp"

Mime::Mime(void)
{
	// <file lastname, mime type>
    _mime_dict.insert(std::pair<std::string, std::string>(".aac", "audio/aac"));
    _mime_dict.insert(std::pair<std::string, std::string>(".abw", "application/x-abiword"));
    _mime_dict.insert(std::pair<std::string, std::string>(".apng", "image/apng"));
    _mime_dict.insert(std::pair<std::string, std::string>(".arc", "application/x-freearc"));
    _mime_dict.insert(std::pair<std::string, std::string>(".avif", "image/avif"));
    _mime_dict.insert(std::pair<std::string, std::string>(".avi", "video/x-msvideo"));
    _mime_dict.insert(std::pair<std::string, std::string>(".azw", "application/vnd.amazon.ebook"));
    _mime_dict.insert(std::pair<std::string, std::string>(".bin", "application/octet-stream"));
    _mime_dict.insert(std::pair<std::string, std::string>(".bmp", "image/bmp"));
    _mime_dict.insert(std::pair<std::string, std::string>(".bz", "application/x-bzip"));
    _mime_dict.insert(std::pair<std::string, std::string>(".bz2", "application/x-bzip2"));
    _mime_dict.insert(std::pair<std::string, std::string>(".cda", "application/x-cdf"));
    _mime_dict.insert(std::pair<std::string, std::string>(".csh", "application/x-csh"));
    _mime_dict.insert(std::pair<std::string, std::string>(".css", "text/css"));
    _mime_dict.insert(std::pair<std::string, std::string>(".csv", "text/csv"));
    _mime_dict.insert(std::pair<std::string, std::string>(".doc", "application/msword"));
    _mime_dict.insert(std::pair<std::string, std::string>(".docx", "application/vnd.openxmlformats-officedocument.wordprocessingml.document"));
    _mime_dict.insert(std::pair<std::string, std::string>(".eot", "application/vnd.ms-fontobject"));
    _mime_dict.insert(std::pair<std::string, std::string>(".epub", "application/epub+zip"));
    _mime_dict.insert(std::pair<std::string, std::string>(".gz", "application/gzip"));
    _mime_dict.insert(std::pair<std::string, std::string>(".gif", "image/gif"));
    _mime_dict.insert(std::pair<std::string, std::string>(".htm", "text/html"));
    _mime_dict.insert(std::pair<std::string, std::string>(".html", "text/html"));
    _mime_dict.insert(std::pair<std::string, std::string>(".ico", "image/vnd.microsoft.icon"));
    _mime_dict.insert(std::pair<std::string, std::string>(".ics", "text/calendar"));
    _mime_dict.insert(std::pair<std::string, std::string>(".jar", "application/java-archive"));
    _mime_dict.insert(std::pair<std::string, std::string>(".jpeg", "image/jpeg"));
    _mime_dict.insert(std::pair<std::string, std::string>(".jpg", "image/jpeg"));
    _mime_dict.insert(std::pair<std::string, std::string>(".js", "text/javascript"));
    _mime_dict.insert(std::pair<std::string, std::string>(".json", "application/json"));
    _mime_dict.insert(std::pair<std::string, std::string>(".jsonld", "application/ld+json"));
    _mime_dict.insert(std::pair<std::string, std::string>(".mid", "audio/midi"));
    _mime_dict.insert(std::pair<std::string, std::string>(".midi", "audio/x-midi"));
    _mime_dict.insert(std::pair<std::string, std::string>(".mjs", "text/javascript"));
    _mime_dict.insert(std::pair<std::string, std::string>(".mp3", "audio/mpeg"));
    _mime_dict.insert(std::pair<std::string, std::string>(".mp4", "video/mp4"));
    _mime_dict.insert(std::pair<std::string, std::string>(".mpeg", "video/mpeg"));
    _mime_dict.insert(std::pair<std::string, std::string>(".mpkg", "application/vnd.apple.installer+xml"));
    _mime_dict.insert(std::pair<std::string, std::string>(".odp", "application/vnd.oasis.opendocument.presentation"));
    _mime_dict.insert(std::pair<std::string, std::string>(".ods", "application/vnd.oasis.opendocument.spreadsheet"));
    _mime_dict.insert(std::pair<std::string, std::string>(".odt", "application/vnd.oasis.opendocument.text"));
    _mime_dict.insert(std::pair<std::string, std::string>(".oga", "audio/ogg"));
    _mime_dict.insert(std::pair<std::string, std::string>(".ogv", "video/ogg"));
    _mime_dict.insert(std::pair<std::string, std::string>(".ogx", "application/ogg"));
    _mime_dict.insert(std::pair<std::string, std::string>(".opus", "audio/opus"));
    _mime_dict.insert(std::pair<std::string, std::string>(".otf", "font/otf"));
    _mime_dict.insert(std::pair<std::string, std::string>(".png", "image/png"));
    _mime_dict.insert(std::pair<std::string, std::string>(".pdf", "application/pdf"));
    _mime_dict.insert(std::pair<std::string, std::string>(".php", "application/x-httpd-php"));
    _mime_dict.insert(std::pair<std::string, std::string>(".ppt", "application/vnd.ms-powerpoint"));
    _mime_dict.insert(std::pair<std::string, std::string>(".pptx", "application/vnd.openxmlformats-officedocument.presentationml.presentation"));
    _mime_dict.insert(std::pair<std::string, std::string>(".rar", "application/vnd.rar"));
    _mime_dict.insert(std::pair<std::string, std::string>(".rtf", "application/rtf"));
    _mime_dict.insert(std::pair<std::string, std::string>(".sh", "application/x-sh"));
    _mime_dict.insert(std::pair<std::string, std::string>(".svg", "image/svg+xml"));
    _mime_dict.insert(std::pair<std::string, std::string>(".tar", "application/x-tar"));
    _mime_dict.insert(std::pair<std::string, std::string>(".tif", "image/tiff"));
    _mime_dict.insert(std::pair<std::string, std::string>(".tiff", "image/tiff"));
    _mime_dict.insert(std::pair<std::string, std::string>(".ts", "video/mp2t"));
    _mime_dict.insert(std::pair<std::string, std::string>(".ttf", "font/ttf"));
    _mime_dict.insert(std::pair<std::string, std::string>(".txt", "text/plain"));
    _mime_dict.insert(std::pair<std::string, std::string>(".vsd", "application/vnd.visio"));
    _mime_dict.insert(std::pair<std::string, std::string>(".wav", "audio/wav"));
    _mime_dict.insert(std::pair<std::string, std::string>(".weba", "audio/webm"));
    _mime_dict.insert(std::pair<std::string, std::string>(".webm", "video/webm"));
    _mime_dict.insert(std::pair<std::string, std::string>(".webp", "image/webp"));
    _mime_dict.insert(std::pair<std::string, std::string>(".woff", "font/woff"));
    _mime_dict.insert(std::pair<std::string, std::string>(".woff2", "font/woff2"));
    _mime_dict.insert(std::pair<std::string, std::string>(".xhtml", "application/xhtml+xml"));
    _mime_dict.insert(std::pair<std::string, std::string>(".xls", "application/vnd.ms-excel"));
    _mime_dict.insert(std::pair<std::string, std::string>(".xlsx", "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"));
    _mime_dict.insert(std::pair<std::string, std::string>(".xml", "application/xml"));
    _mime_dict.insert(std::pair<std::string, std::string>(".xul", "application/vnd.mozilla.xul+xml"));
    _mime_dict.insert(std::pair<std::string, std::string>(".zip", "application/zip"));
    _mime_dict.insert(std::pair<std::string, std::string>(".3gp", "video/3gpp"));
    _mime_dict.insert(std::pair<std::string, std::string>(".3g2", "video/3gpp2"));
    _mime_dict.insert(std::pair<std::string, std::string>(".7z", "application/x-7z-compressed"));
}

std::string Mime::get_mime_type(std::string filename)
{
	std::string lastname;
	size_t pos;

	pos = filename.find('.');

	std::cout << "bp3.4" << std::endl;
	if (pos == std::string::npos)
		std::cerr << "file name not contain \'.\' Charactor." << std::endl;
	std::cout << "bp3.5" << std::endl;
	lastname = filename.substr(pos);
	std::cout << "bp3.6" << std::endl;
	std::map<std::string, std::string>::iterator mime_pair = _mime_dict.find(lastname);

	std::cout << "bp3.7" << std::endl;
	return (std::string(mime_pair->second));

}
