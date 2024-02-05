#include "helper.h"

std::vector<std::string> Helper::Split(const std::string text,
                                       const std::string delim) {
    std::vector<std::string> list;

    char *text_dup = (char *)text.c_str();  // duplicate string as char*
    const char *delim_ptr = delim.c_str();
    char *ptr = strtok(text_dup, delim_ptr);

    while (ptr != NULL) {
        std::string str;
        str.assign(ptr);
        list.push_back(str);
        ptr = strtok(NULL, delim_ptr);
    }

    return list;
}

std::string Helper::Join(const std::vector<std::string> texts, const char *delim) {
    std::ostringstream imploded;
    std::copy(texts.begin(), texts.end(),
              std::ostream_iterator<std::string>(imploded, delim));
    return imploded.str();
}