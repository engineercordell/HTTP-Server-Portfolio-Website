let terminalCancelToken = { canceled: false };
let aboutCancelToken = { canceled: false };
let hobbiesCancelToken = { canceled: false };
let learnCancelToken = { canceled: false };
let skillsCancelToken = { canceled: false };
let aboutHasAnimated = false;
let hobbiesHasAnimated = false;
let learnHasAnimated = false;
let skillsHasAnimated = false;

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
  const aboutObserver = new IntersectionObserver(handleAboutMeReveal, { threshold: 0.3 });
  const hobbiesObserver = new IntersectionObserver(handleHobbiesReveal, { threshold: 0.3 });
  const learnObserver = new IntersectionObserver(handleLearningReveal, { threshold: 0.3 });
  const skillsObserver = new IntersectionObserver(handleSkillsReveal, { threshold: 0.3 });

  const aboutSection = document.getElementById('about-me');
  aboutObserver.observe(aboutSection);
  const hobbiesSection = document.getElementById('hobbies');
  hobbiesObserver.observe(hobbiesSection);
  const learnSection = document.getElementById('learn');
  learnObserver.observe(learnSection);
  const skillsSection = document.getElementById('skills');
  skillsObserver.observe(skillsSection);
});
document.getElementById('terminal-panel').addEventListener("click", async () => {
    terminalCancelToken.canceled = true;

    const lastTerminalCursor = document.getElementById("terminal-cursor");
    if (lastTerminalCursor) lastTerminalCursor.remove();
});
// 'about-background' is clicked
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

        await typeText("./skills --list", 50, "skills-command", "skills-cursor", skillsCancelToken);
        await sleep(200);

        const skillsGrid = document.getElementById('skills-grid');
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