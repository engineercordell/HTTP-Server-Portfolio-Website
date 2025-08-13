let terminalCancelToken = { canceled: false };
let aboutCancelToken = { canceled: false };
let hobbiesCancelToken = { canceled: false };
let learnCancelToken = { canceled: false };
let skillsCancelToken = { canceled: false };
let projectsCancelToken = { canceled: false };
let aboutHasAnimated = false;
let hobbiesHasAnimated = false;
let learnHasAnimated = false;
let skillsHasAnimated = false;
let projectsHasAnimated = false;
let capstoneHasAnimated = false;
const isTouch = window.matchMedia('(pointer: coarse) and (pointer: coarse)').matches;

const hobbies = [
    "🏋️ Gym/Weightlifting",
    "📕 Reading",
    "🎮 Playing Video Games",
    "📺 Watching Anime"
];
const learn = [
    "🧠 Computer Systems: A Programmer's Perspective — Finished!",
    "📘 Operating Systems: Three Easy Pieces (OSTEP) — In Progress",
    "📘 Operating Systems: Principles and Practice — In Progress",
    "📘 xv6: Unix-like OS — Tinkering in progress",
    "📘 Linux Kernel Development (Third Edition) — In Progress",
    "📘 Computer Architecture: A Quantitative Approach (Hennesey and Patterson) — Coming up next",
    "📡 TCP/IP Illustrated — Coming up next",
    "💡 Crafting Interpreters — Long-term goal",
    "🔧 Makefiles & Build Systems — Practicing with this HTTP server"
];
const skills = {
    "C++": {
        years: 2,
        description: 
            `<ul>
                <li>- Built a multithreaded HTTP server and capstone software using C++.</li>
                <li>- Applied in Arduino projects and systems-level programming.</li>
                <li>- Currently my primary low-level development language.</li>
            </ul>`
    },
    "C": {
        years: 2,
        description:
            `<ul>
                <li>- First learned via Arduino projects in high school; solidified through architecture courses in college.</li>
                <li>- Extensively used in class labs, assignments, and built a mini-game for the GBA emulator.</li>
                <li>- Used extensively in Computer Organization projects (see below).</li>
            </ul>`
    },
    "Assembly": {
        years: 2,
        description:
            `<ul>
                <li>- Learned LC-3 to understand CPU architecture, instruction sets, and memory systems.</li>
                <li>- Built a simulated word-addressable CPU in CircuitSim using Assembly logic.</li>
            </ul>`
    },
    "Python": {
        years: 6,
        description:
            `<ul>
                <li>- Used across AI/ML courses to implement search, inference, and learning algorithms.</li>
                <li>- Built deep learning models and automated scripts (e.g., class registration).</li>
                <li>- First learned via personal projects in high school.</li>
            </ul>`
    },
    "Java": {
        years: 9, 
        description:
            `<ul>
                <li>- First language I taught myself in-depth and applied through FIRST Robotics in high school.</li>
                <li>- Used to update Minecraft mods like Tinkers' Construct and plugins (e.g., Avatar plugin).</li>
                <li>- Utilized in college courses: Intro to OOP and Data Structures & Algorithms.</li>
            </ul>`
    },
    "C#": {
        years: 3,
        description:
            `<ul>
                <li>- Learned primarily to develop mods for Terraria using tModLoader.</li>
                <li>- Gained familiarity with object-oriented patterns and game scripting.</li>
                <li>- Project was never completed due to academic workload, but solidified foundational C# skills.</li>
            </ul>`
    },
    "MATLAB": {
        years: 5,
        description:
            `<ul>
                <li>- Used across 6+ mechanical engineering courses for simulation, control systems, and data analysis.</li>
                <li>- Applied in robotics, PID tuning, force mechanics, GPS navigation, and experimental lab reporting.</li>
            </ul>`
    },
    "HTML": {
        years: 4,
        description:
            `<ul>
                <li>- Studied extensively through freeCodeCamp and The Odin Project.</li>
                <li>- Deepened understanding of semantic HTML and accessibility practices.</li>
                <li>- This portfolio site is my first formal showcase of accumulated web dev knowledge.</li>
            </ul>`
    },
    "CSS": {
        years: 4,
        description:
            `<ul>
                <li>- Learned via freeCodeCamp and The Odin Project alongside HTML and JS.</li>
                <li>- Focused heavily on layout systems (Flexbox, Grid) and visual effects.</li>
                <li>- Used advanced techniques like <code>clip-path</code> and <code>mask</code> on this site.</li>
            </ul>`
    },
    "JavaScript": {
        years: 4,
        description:
            `<ul>
                <li>- Gained proficiency via The Odin Project and freeCodeCamp.</li>
                <li>- Comfortable with DOM manipulation, event handling, and async logic.</li>
                <li>- Used throughout this portfolio site to enhance interactivity and UI behavior.</li>
            </ul>`
    },
    "ESP32": {
        years: 1,
        description:
            `<ul>
                <li>- Used as the central microcontroller for my Capstone project.</li>
                <li>- Handled TEC and fan control, Bluetooth/WiFi communication, and live data plotting.</li>
                <li>- Served as an access point to remotely control the system via a client interface.</li>
            </ul>`
    },
    "Raspberry Pi": {
        years: 1, // Even if it's been a while, this reflects that one significant project
        description:
            `<ul>
                <li>- First used during high school science fair project to control a remote-access live-streamed security camera system.</li>
                <li>- Gained foundational experience with Linux-based single-board computing and camera integration.</li>
            </ul>`
    },
    "Arduino": {
        years: 3,
        description:
            `<ul>
                <li>- Built an autonomous robot in middle school for a science fair using Arduino.</li>
                <li>- Later used it in a college design course to build and program a robot for a sponsor-backed design competition.</li>
                <li>- Familiar with integrating sensors, motors, and prototyping embedded systems using the Arduino IDE.</li>
            </ul>`
    },
    "Oscilloscope": {
        years: 2,
        description:
            `<ul>
                <li>- Used regularly in ECE 3741 to measure, analyze, and debug analog and mixed-signal circuits.</li>
                <li>- Applied in lab settings for building op-amp filters, rectifiers, speaker amplifiers, and more.</li>
            </ul>`
    },
    "Function Generator": {
        years: 2,
        description:
            `<ul>
                <li>- Used in conjunction with oscilloscopes in ECE lab courses to test circuit response to various waveforms.</li>
                <li>- Provided stimulus signals for filters, comparators, and other analog designs during op-amp labs.</li>
            </ul>`
    },
    "PyTorch": {
        years: 1,
        description:
            `<ul>
                <li>- Used as a high-level framework to implement neural networks and image transformation tasks.</li>
                <li>- Supplemented assignments involving CNNs, Random Forests, and deep learning workflows.</li>
            </ul>`
    },
    "TensorFlow": {
        years: 1,
        description:
            `<ul>
                <li>- Employed in parallel with PyTorch to explore deep learning architectures and optimization.</li>
                <li>- Utilized in image-based analysis and supervised learning pipelines.</li>
            </ul>`
    },
    "NumPy": {
        years: 1,
        description:
            `<ul>
                <li>- Used extensively for vectorized computation and matrix operations across all ML assignments.</li>
                <li>- Enabled fast, memory-efficient implementations of clustering, regression, and image processing.</li>
            </ul>`
    },
    "Matplotlib": {
        years: 1,
        description:
            `<ul>
                <li>- Used to visualize data distributions, loss curves, and clustering results.</li>
                <li>- Plotted training accuracy and model outputs across multiple ML experiments.</li>
            </ul>`
    },
    "Pandas": {
        years: 1,
        description:
            `<ul>
                <li>- Utilized for dataset manipulation, preprocessing, and feature selection tasks.</li>
            </ul>`
    },
        "SolidWorks": {
        years: 4,
        description:
            `<ul>
                <li>- Learned in ME 1670 for sketching and 3D modeling, including projects like a rubber band crossbow and a rocket-propelled scooter.</li>
                <li>- Applied across undergrad, including capstone and Machine Design, to model mechanical components and assemblies for analysis and prototyping.</li>
            </ul>`
    },
    "Autodesk Inventor": {
        years: 1,
        description:
            `<ul>
                <li>- Introduced during high school engineering courses alongside manual sketching and basic GD&T concepts.</li>
                <li>- Practiced 3D modeling fundamentals before transitioning fully to SolidWorks in college.</li>
            </ul>`
    },
    "Ultimaker Cura": {
        years: 3,
        description:
            `<ul>
                <li>- Used extensively in ME 2110 to slice 3D models for printing functional parts for a robotics design project.</li>
                <li>- Familiar with printer settings and print optimization for PLA components.</li>
            </ul>`
    },
    "Laser Cutting": {
        years: 3,
        description:
            `<ul>
                <li>- Experience dating back to high school and further developed in ME 2110 to fabricate custom MDF robot chassis.</li>
                <li>- Comfortable preparing cut files and operating laser equipment for structural and aesthetic parts.</li>
            </ul>`
    },
    "Soldering": {
        years: 5,
        description:
            `<ul>
                <li>- Began in middle school wiring autonomous robots for science fair projects; continued through college-level robotics and capstone design.</li>
                <li>- Proficient in soldering wires and SMD components onto PCBs; built motor controller harnesses using MOSFETs.</li>
            </ul>`
    },
    "Mill & Shop Tools": {
        years: 4,
        description:
            `<ul>
                <li>- Hands-on experience with drill presses, table saws, band saws, and cutting tools.</li>
                <li>- Developed during ME 2110 and further refined during prototyping instructor training sessions.</li>
            </ul>`
    },
    "Technical Drawings": {
        years: 4,
        description:
            `<ul>
                <li>- Introduced to engineering drawings in high school; expanded in ME 1670 with practice in GD&T, tolerancing, and BOM preparation.</li>
                <li>- Used to communicate precise design intent for fabrication and team collaboration.</li>
            </ul>`
    }
}

// when page is loaded, 'terminal' animation plays
document.addEventListener('DOMContentLoaded', async () => {
    await sleep(750);
    await typeText("Visitor detected", 40, "terminal-command-text", "terminal-cursor", terminalCancelToken);
    await sleep(1000);
    await typeText("...", 300, "terminal-command-text", "terminal-cursor", terminalCancelToken);
    await sleep(1000);
    await typeText("executing", 40, "terminal-command-text", "terminal-cursor", terminalCancelToken);
    await typeText("\u00A0greetings.exe", 40, "terminal-command-program", "terminal-cursor", terminalCancelToken);
    await typeText("...", 40, "terminal-command-ellipsis", "terminal-cursor", terminalCancelToken);
    await sleep(1000);

    const terminal = document.getElementById('terminal-text');

    const descLine = document.createElement('div');
    descLine.classList.add('terminal-desc');
    descLine.innerHTML = `
        <span class="text-wrapper">
            <span id="terminal-desc-text"></span>
        </span>
    `;
    terminal.appendChild(descLine);
    await typeText("Hello there, I'm Cordell. A multifaceted Georgia Tech engineer.", 20, "terminal-desc-text", "terminal-cursor", terminalCancelToken);

    const aboutLine = document.createElement('div');
    aboutLine.classList.add('terminal-more');
    aboutLine.innerHTML = `
        <span class="text-wrapper">
            <span id="terminal-more-text"></span>
        </span>
    `;
    terminal.appendChild(aboutLine);
    await typeText("Click 'Resume' above to download my resume, or keep scrolling to learn more about me!", 20, "terminal-more-text", "terminal-cursor", terminalCancelToken);
});
// when page is loaded, add observers
document.addEventListener('DOMContentLoaded', () => {
    const aboutObserver = new IntersectionObserver(handleAboutMeReveal, { threshold: 0.2 });
    const hobbiesObserver = new IntersectionObserver(handleHobbiesReveal, { threshold: 0.2 });
    const learnObserver = new IntersectionObserver(handleLearningReveal, { threshold: 0.1 });
    const skillsObserver = new IntersectionObserver(handleSkillsReveal, { threshold: 0.1 });
    const projectsObserver = new IntersectionObserver(handleProjectsReveal, { threshold: 0.1 });

    const aboutSection = document.getElementById('about-me');
    aboutObserver.observe(aboutSection);
    const hobbiesSection = document.getElementById('hobbies');
    hobbiesObserver.observe(hobbiesSection);
    const learnSection = document.getElementById('learn');
    learnObserver.observe(learnSection);
    const skillsSection = document.getElementById('skills');
    skillsObserver.observe(skillsSection);
    const projectsSection = document.getElementById('projects');
    projectsObserver.observe(projectsSection);

    // Projects Mobile Device Event Listeners
    const cards = document.querySelectorAll('.project-img-wrapper');
    if (isTouch) {
        cards.forEach(card => {
            card.addEventListener('click', (e) => {
                if (e.target.closest('a, button')) return;

                if (card.classList.contains('expanded')) {
                    card.classList.remove('expanded');
                } else {
                    cards.forEach(c => c.classList.remove('expanded'));
                    card.classList.add('expanded');
                }
            });
        });
    }
});
document.getElementById('terminal-panel').addEventListener("click", async () => {
    terminalCancelToken.canceled = true;

    const lastTerminalCursor = document.getElementById("terminal-cursor");
    if (lastTerminalCursor) lastTerminalCursor.remove();
});
document.getElementById("about-background").addEventListener("click", async () => {
    aboutCancelToken.canceled = true;

    const lastAboutCursor = document.getElementById("about-cursor");
    if (lastAboutCursor) lastAboutCursor.remove();
});
document.getElementById("hobbies").addEventListener("click", async () => {
    hobbiesCancelToken.canceled = true;

    const lastHobbiesCursor = document.getElementById("about-cursor");
    if (lastHobbiesCursor) lastHobbiesCursor.remove();
});
document.getElementById("learn").addEventListener("click", async () => {
    learnCancelToken.canceled = true;

    const lastLearnCursor = document.getElementById("learn-cursor");
    if (lastLearnCursor) lastLearnCursor.remove();
});

// set up each skill event listener
document.querySelectorAll(".skill-transform-wrapper").forEach(wrapper => {
    const skillDiv = wrapper.querySelector(".skill");
    const tooltip = wrapper.querySelector(".skill-tooltip");
    const skillObj = skills[skillDiv.dataset.skill];

    if (!skillObj) return;

    const [backColor, skillObjColor] = getExperienceColor(skillObj.years);

    if (isTouch) {
        skillDiv.addEventListener('click', (e) => {
            e.stopPropagation();

            const isAlreadyActive = tooltip.classList.contains('active');

            document.querySelectorAll('.skill-tooltip.active').forEach(t => {                
                const parentWrapper = t.closest('.skill-transform-wrapper');
                const parentSkillDiv = parentWrapper.querySelector('.skill');
                const parentSkillObj = skills[parentSkillDiv.dataset.skill];
                const [parentBackColor] = getExperienceColor(parentSkillObj.years);

                parentSkillDiv.style.backgroundColor = '';
                parentSkillDiv.classList.remove(`hover-${parentBackColor}`, 'active');
                t.style.opacity = 0;
                t.classList.remove('active');
            });

            if (!isAlreadyActive) {
                skillDiv.classList.add(`hover-${backColor}`, 'active');
                skillDiv.style.backgroundColor = skillObjColor;
                tooltip.style.backgroundColor = skillObjColor;
                tooltip.innerHTML = `
                    <span style="color: ${skillObjColor}; font-weight: bold;">${skillObj.years} Years of Experience</span>
                    <br>
                    <br>
                    <span style="display: inline-block; text-align: left;">${skillObj.description}</span>
                `;
                tooltip.style.opacity = 1;
                tooltip.classList.add('active');
            }
        });

        document.addEventListener('click', () => {
            document.querySelectorAll('.skill-tooltip.active').forEach(t => {
                const parentWrapper = t.closest('.skill-transform-wrapper');
                const parentSkillDiv = parentWrapper.querySelector('.skill');
                const parentSkillObj = skills[parentSkillDiv.dataset.skill];
                const [parentBackColor] = getExperienceColor(parentSkillObj.years);

                parentSkillDiv.style.backgroundColor = '';
                parentSkillDiv.classList.remove(`hover-${parentBackColor}`, 'active');
                t.style.opacity = 0;
                t.classList.remove('active');
            });
        });
    } else {
        skillDiv.addEventListener('mouseenter', () => {
            skillDiv.classList.add(`hover-${backColor}`);
            skillDiv.style.backgroundColor = skillObjColor;
            tooltip.style.backgroundColor = skillObjColor;
            tooltip.innerHTML = `
                <span style="color: ${skillObjColor}; font-weight: bold;">${skillObj.years} Years of Experience</span>
                <br>
                <br>
                <span style="display: inline-block; text-align: left;">${skillObj.description}</span>
            `;
            tooltip.style.opacity = 1;
        });

        skillDiv.addEventListener('mouseleave', () => {
            skillDiv.style.backgroundColor = '';
            skillDiv.classList.remove(`hover-${backColor}`);
            tooltip.style.opacity = 0;
        });
    }
});

async function handleAboutMeReveal(entries) {
  const entry = entries[0];
  if (entry.isIntersecting && !aboutHasAnimated) {
    aboutHasAnimated = true;

    await typeText("./about-me", 50, "about-command", "about-cursor", aboutCancelToken);
    await sleep(200);

    await typeText("Background", 1, "about-back-head", "about-cursor", aboutCancelToken);
    await typeText(`
        Hey there—My name is Cordell Palmer. In December 2024, I graduated from Georgia Tech 
        with a Bachelor of Science in Mechanical Engineering and a Minor in Computer Science, with a focus on Machine Learning.
        During my undergraduate years, I was able to cultivate a broad set of skills, having obtained proficiency in areas such as
        CAD modeling/3D printing, structural analysis, software and hardware programming, AI, robotics, and wide range of electrical and mechanical
        data analysis/manufacturing tools. Despite my background being primarily rooted in mechanical systems, my true passion lies at the intersection of hardware, 
        software, and AI development.`, 1, "about-line-1", "about-cursor", aboutCancelToken);
    await typeText(`
        Since graduation I've deeply immersed myself in systems development, having written the HTTP server that
        runs this website from scratch in C++ with barebones kernel APIs. The journey to enrich my understanding of networking, memory, and 
        OS-level architecture has sparked an ever evolving passion in all things embedded systems, FPGAs, digital circuitry, and future-forward
        technologies like graphene semiconductors.`, 1, "about-line-2", "about-cursor", aboutCancelToken);
    await typeText("In short: I enjoy building things that closely interact with our world, and this is only the beginning.", 1, "about-line-3", "about-cursor", aboutCancelToken);
    await sleep(200);
  }
}
async function handleHobbiesReveal(entries) {
    const entry = entries[0];
    if (entry.isIntersecting && !hobbiesHasAnimated) {
        hobbiesHasAnimated = true;

        await typeText("Hobbies", 50, "hobbies-header", "hobbies-cursor", hobbiesCancelToken);
        await typeText("Engineering can be exhausting, so I enjoy winding down in the following ways:", 1, "hobbies-text", "hobbies-cursor", hobbiesCancelToken);
        await typeListItems("hobbies-list", hobbies, "hobbies-item", 1, 200, "hobbies-cursor", hobbiesCancelToken);
    }
}
async function handleLearningReveal(entries) {
    const entry = entries[0];
    if (entry.isIntersecting && !learnHasAnimated) {
        learnHasAnimated = true;

        await typeText("Currently Learning", 50, "learn-header", "learn-cursor", learnCancelToken);
        await typeText("Here's a list of topics/books I'm interested in learning/have learned:", 1, "learn-text", "learn-cursor", learnCancelToken);
        await typeListItems("learn-list", learn, "learn-item", 1, 200, "learn-cursor", learnCancelToken);
    }
}
async function handleSkillsReveal(entries) {
    const entry = entries[0];
    if (entry.isIntersecting && !skillsHasAnimated) {
        skillsHasAnimated = true;

        const skillsGrid = document.getElementById('skills-grid');

        await typeText("./skills --list", 50, "skills-command", "skills-cursor", skillsCancelToken);

        const skillOverview = document.getElementById('skill-overview');
        skillOverview.classList.remove('overview-wrapper-hidden');
        skillOverview.classList.add('overview-wrapper');

        await sleep(1000);

        const skillColumns = skillsGrid.querySelectorAll('.skill-column');

        let baseDelay = 0;

        skillColumns.forEach((column) => {
            const category = column.querySelector('.skill-category');
            const skills = column.querySelectorAll('.skill-transform-wrapper');

            category.style.transition = 'opacity 1s ease, transform 1s ease';
            category.style.transitionDelay = `${baseDelay}s`;
            category.classList.add('visible');

            baseDelay += 0.1;

            skills.forEach((skill, skillIndex) => {
                const delay = baseDelay + skillIndex * 0.1;
                skill.style.transition = 'opacity 0.8s ease, transform 0.8s ease';
                skill.style.transitionDelay = `${delay}s`;
                skill.classList.add('visible');

                setTimeout(() => {
                    skill.classList.add('hover-ready');
                }, delay * 1000);
            });

            baseDelay += skills.length * 0.1 + 0.3;
        });
    }
}
const projects = document.getElementById("projects");
const capstone = document.getElementById("capstone-details");
const backButton = document.getElementById("back-button");
document.getElementById("capstone-button").addEventListener("click", async () => {
    projects.classList.add('learn-more-hide');

    await sleep(1000);
    capstone.classList.add('capstone-show');
});
document.getElementById("back-button").addEventListener("click", async () => {
    capstone.classList.remove('capstone-show');

    await sleep(1000);
    projects.classList.remove('learn-more-hide');
});
async function handleProjectsReveal(entries) {
    const entry = entries[0];
    if (entry.isIntersecting && !projectsHasAnimated) {
        projectsHasAnimated = true;

        await typeText("./projects --list", 50, "projects-command", "projects-cursor", projectsCancelToken);

        const projectOverview = document.getElementById('projects-overview');

        projectOverview.classList.remove('overview-wrapper-hidden');
        projectOverview.classList.add('overview-wrapper');

        await sleep(500);

        delay = 0;

        const projectCards = document.getElementById('projects-grid').querySelectorAll('.project-card-hidden');
        projectCards.forEach((card) => {
            card.classList.remove('project-card-hidden');
            card.classList.add('project-card');
            card.style.transitionDelay = `${delay}s`;
            delay += 0.5;
        });
    }
}

async function typeText(text, delay, targetID, cursorID, cancelToken, removeCursorOnEnd = true) {
    const targetEl = document.getElementById(targetID);

    const oldCursor = document.getElementById(cursorID);
    if (oldCursor) oldCursor.remove();

    const cursorSpan = document.createElement("span");
    cursorSpan.classList.add("cursor");
    cursorSpan.textContent = "_";
    targetEl.appendChild(cursorSpan);

    for (let i = 0; i < text.length; i++) {
        if (cancelToken.canceled) {
            targetEl.insertAdjacentText("beforeend", text.slice(i));
            break;
        }
        cursorSpan.insertAdjacentText("beforebegin", text[i]);
        await sleep(delay);
    }

    if (removeCursorOnEnd) {
        cursorSpan.remove();
    }
}

async function typeListItems(listID, listItems, listItemClassName, charDelay, delayBetween, cursorID, token) {
    const listContainer = document.getElementById(listID);

    listContainer.innerHTML = "";

    for (const text of listItems) {
        const li = document.createElement("li");
        li.classList.add(listItemClassName);

        const emoji = document.createElement("span");
        emoji.classList.add("emoji");
        emoji.textContent = text.slice(0, 2);

        li.appendChild(emoji);
        listContainer.appendChild(li);

        await typeText(text.slice(2), charDelay, li.id = crypto.randomUUID(), cursorID, token);
        await sleep(delayBetween);
    }
}

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}
// Returns first color to apply background color and second color to apply skill color
function getExperienceColor(yoe) {
    switch (yoe) {
        case 1:
            return ["novice", "white"];
        case 2:
        case 3:
            return ["beginner", "green"];
        case 4:
            return ["proficient", "blue"];
        case 5:
            return ["expert", "purple"];
        default:
            return ["master", "gold"];
    }
}