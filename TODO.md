# HTTPS Server
Lightweight HTTPS server written in C++

### Security
- [ ] Prevent servicing a file that's outside of 'public/'

### Optimizations
- [ ] Optimize header parsing loop  
  - [ ] Call find() once to obtain all LF
- [✓] Use a case-insensitive map (std::unordered_map<std::string, std::string, ci_hash, ci_equal>).
- [ ] Handle multi-line folded headers (rare in HTTP/1.1, but good to know).
- [ ] Guard against maliciously malformed headers
- [ ] Refactor magic numbers in http_request_header.cpp
  - [ ] Consider std::isspace()
- [ ] Handle how the construction of HTTPRequestHeader obj can throw and properly clean up

### Completed Column ✓
- [x] Completed task title  