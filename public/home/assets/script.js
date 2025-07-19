let terminalCancelToken = { canceled: false };
let aboutCancelToken = { canceled: false };
let aboutHasAnimated = false;

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

// when page is loaded, observe when 'about-me' scrolls into view
document.addEventListener('DOMContentLoaded', () => {
  const observer = new IntersectionObserver(handleAboutMeReveal, { threshold: 0.3 });

  const aboutSection = document.getElementById('about-me');
  observer.observe(aboutSection);
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

// each 'section/content-div' will have it's own typeText() to dynamically write to it
// const sections = {
//     "about-section": [
//         { text: "./about-me", delay: 50, targetID: "about-command", removeCursor: true},
//         { text: "Background", delay: 1, targetID: "about-back-head", removeCursor: true},
//         { text: `Hey there—My name is Cordell Palmer. In December 2024, I graduated from Georgia Tech 
//             with a Bachelor of Science in Mechanical Engineering and a Minor in Computer Science, with a focus on Machine Learning.
//             During my undergraduate years, I was able to cultivate a broad set of skills, having obtained proficiency in areas such as
//             CAD modeling/3D printing, structural analysis, software and hardware programming, AI, robotics, and wide range of electrical and mechanical
//             data analysis/manufacturing tools. Despite my background being primarily rooted in mechanical systems, my true passion lies at the intersection of hardware, 
//             software, and AI development.`, 
//         delay: 1, 
//         targetID: "about-line-1", 
//         removeCursor: true},
//         { text: `Since graduation I've deeply immersed myself in systems development, having written the HTTP server that
//             runs this website from scratch in C++ with barebones kernel APIs. The journey to enrich my understanding of networking, memory, and 
//             OS-level architecture has sparked an ever evolving passion in all things embedded systems, FPGAs, digital circuitry, and future-forward
//             technologies like graphene semiconductors.`, 
//         delay: 1, 
//         targetID: "about-line-2", 
//         removeCursor: true},
//         { text: "In short: I enjoy building things that closely interact with our world, and this is only the beginning.",
//         delay: 1,
//         targetID: "about-line-3",
//         removeCursor: true}
//     ],
//     "hobbies-section": [
//         { text: "Hobbies", delay: 1, targetID: "hobbies-head", removeCursor: true },
//         { text: "Engineering can be exhausting, so I like to wind down in the following ways:", delay: 1, targetID: "hobbies-text-span", removeCursor: true},
//         { text: ""}
//     ]
// }

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}