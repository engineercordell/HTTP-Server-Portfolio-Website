# HTTPS Server
Lightweight HTTPS server written in C++

### Security
- [✓] Prevent servicing a file that's outside of 'public/'
- [ ] Implement a std::set<std::string> to act as an IP blacklist whenever an incoming connection is about to be accepted
- [ ] Guard against maliciously malformed headers

### Optimizations
- [ ] Optimize header parsing loop  
  - [ ] Call find() once to obtain all LF
- [✓] Use a case-insensitive map (std::unordered_map<std::string, std::string, ci_hash, ci_equal>).
- [ ] Handle multi-line folded headers (rare in HTTP/1.1, but good to know).
- [ ] Refactor magic numbers in http_request_header.cpp
  - [ ] Consider std::isspace()
- [✓] Handle how the construction of HTTPRequestHeader obj can throw and properly clean up
- [ ] Add persistent connections or HTTP/1.1 features
- [✓] Start parsing .css/.js files to support full page serving
- [ ] Refactor toward epoll or select() for async IO

## Features
- [ ] Change log files at runtime
- [ ] Rotate logs based on date, size, time, etc.

### Completed Column ✓
- [x] Completed task title  