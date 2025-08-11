# HTTPS Server
Lightweight HTTPS server written in C++

## MUST DO 
- [ ] Add a 'back button' for 'learn more' button
- [ ] Create animation for 'learn more' button
- [ ] Enable toggle on 'Skills' section
- [ ] Make 'Skills' section mobile-friendly
- [ ] Make 'About Me' mobile-friendly
- [ ] Make the navigation bar mobile-friendly by shrinking to hold two ellipsis on each side and when clicked trigger the drop down on a particular side
- [ ] Add icons and links for 'LinkedIn' and 'GitHub' on navigation bar
- [ ] Fix toggle-to-skip animation
- [ ] Ensure landing page terminal is mobile-friendly
- [ ] Tidy up landing page terminal
- [ ] Add my picture
- [ ] Add 'Contact Me' section

## Future Projects to Add
- [ ] Recession Predictor Proj
- [ ] CS 3600 Projs
- [ ] Machine Design Projects 2 & 3
- [ ] Robotics Labs
- [ ] MechE Technical Report Writing and Experimentation Reports
- [ ] MechE CAD Personal Proj & Final Proj

## Security
- [✓] Prevent servicing a file that's outside of 'public/'
- [ ] Implement a std::set<std::string> to act as an IP blacklist whenever an incoming connection is about to be accepted
- [ ] Guard against maliciously malformed headers

## Optimizations
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

## Website
- [ ] In the case of a font retrieval failure, I will need to adjust navbar size automatically to accomodate for increase/shrink in size of text
- [ ] Ensure video replays when clicking back on tab
- [✓] About Me Sections
  - [✓] Hobbies
  - [✓] Currently Learning
- [ ] Handle embedded content
  