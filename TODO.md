# HTTPS Server
Lightweight HTTPS server written in C++

## MUST DO 
- [✓] Add a 'back button' for 'learn more' button
- [✓] (UNNCESSARY) Create animation for 'learn more' button
- [✓] Make 'Projects' section mobile-friendly
- [✓] Enable toggle on 'Skills' section for mobile devices
- [✓] Make 'Skills' section mobile-friendly
- [✓] Make the navigation bar mobile-friendly
- [✓] Add icons for 'LinkedIn' and 'GitHub' on navigation bar
- [✓] Add links for 'LinkedIn' and 'GitHub' on navigation bar
- [✓] Make 'Landing Page' section mobile-friendly
- [✓] Tidy up 'Landing Page' terminal
- [✓] Fix toggle-to-skip animation
- [✓] Make 'About Me' section mobile-friendly
- [✓] Add my picture
- [ ] Add 'Contact Me' section
- [ ] Fix 'Project' section and 'Contact Me' section overlap
- [ ] Fix Capstone Project buttons not working
- [ ] Fix large fonts on small displays in 'Project' section
- [ ] Resume should download resume
- [ ] Get rid of 'GitHub' and 'LinkedIn' on navbar
- [ ] Add pulsing effect to nav bar regardless of display

## Future Projects to Add
- [✓] Recession Predictor Proj
- [ ] Machine Learning Projs
- [ ] Intro to AI Projs
- [ ] Machine Design Projs 2 & 3
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
  