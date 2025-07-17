document.addEventListener('DOMContentLoaded', async () => {
    await sleep(750);
    await typeText("Visitor detected", 40, "terminal-command-text");
    await sleep(1000);
    await typeText("...", 300, "terminal-command-text");
    await sleep(1000);
    await typeText("executing", 40, "terminal-command-text");
    await typeText("\u00A0greetings.exe", 40, "terminal-command-program");
    await typeText("...", 40, "terminal-command-ellipsis");
    await sleep(500);
    document.querySelector('.cursor').classList.add('stopped');
    await sleep(500);

    const terminal = document.querySelector('.terminal-text');
    let oldCursor = document.querySelector('.terminal-command .cursor');
    oldCursor.remove();
    const descLine = document.createElement('div');
    descLine.classList.add('terminal-desc');
    descLine.innerHTML = `
        <span class="text-wrapper">
            <span id="terminal-desc-text"></span><span class="cursor">_</span>
        </span>
    `;
    terminal.appendChild(descLine);
    await typeText("Hello there, I'm Cordell. A multifaceted Georgia Tech engineer.", 20, "terminal-desc-text");
    oldCursor = document.querySelector('.terminal-desc .cursor');
    oldCursor.remove();

    const aboutLine = document.createElement('div');
    aboutLine.classList.add('terminal-more');
    aboutLine.innerHTML = `
        <span class="text-wrapper">
            <span id="terminal-more-text"></span><span class="cursor">_</span>
        </span>
    `;
    terminal.appendChild(aboutLine);
    await typeText("Click 'Resume' above to download my resume, or keep scrolling to learn more about me!", 20, "terminal-more-text");

    oldCursor = document.querySelector('.terminal-more .cursor');
    oldCursor.remove();
});

// about-me listener
document.addEventListener('DOMContentLoaded', () => {
  const observer = new IntersectionObserver(handleAboutMeReveal, {
    threshold: 0.1
  });

  const aboutSection = document.getElementById('about-me');
  observer.observe(aboutSection);
});

let aboutHasAnimated = false;

async function handleAboutMeReveal(entries) {
  const entry = entries[0];
  if (entry.isIntersecting && !aboutHasAnimated) {
    aboutHasAnimated = true;

    await typeTextAdvanced("./about-me", 50, "about-command", true);
    await sleep(200);

    await typeTextAdvanced("Background", 5, "about-back-head", true);

    await typeTextAdvanced(`
        Hey there—My name is Cordell Palmer. In December 2024, I graduated from Georgia Tech 
        with a Bachelor of Science in Mechanical Engineering and a Minor in Computer Science, with a focus on Machine Learning.
        During my undergraduate years, I was able to cultivate a broad set of skills, having obtained proficiency in areas such as
        CAD modeling/3D printing, structural analysis, software and hardware programming, AI, robotics, and wide range of electrical and mechanical
        data analysis/manufacturing tools. Despite my background being primarily rooted in mechanical systems, my true passion lies at the intersection of hardware, 
        software, and AI development.`, 5, "about-line-1", true);

    await typeTextAdvanced(`
        Since graduation I've deeply immersed myself in systems development, having written the HTTP server that
        runs this website from scratch in C++ with barebones kernel APIs. The journey to enrich my understanding of networking, memory, and 
        OS-level architecture has sparked an ever evolving passion in all things embedded systems, FPGAs, digital circuitry, and future-forward
        technologies like graphene semiconductors.
        `, 5, "about-line-2", true);

    await typeTextAdvanced("In short: I enjoy building things that closely interact with our world, and this is only the beginning.", 5, "about-line-3", true);
  }
}


function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

async function typeText(text, charDelay, elemID) {

    return new Promise((resolve) => {
        const target = document.getElementById(elemID);
        let index = 0;

        function typeChar() {
            if (index < text.length) {
                target.textContent += text.charAt(index);
                index++;
                setTimeout(typeChar, charDelay);
            } else {
                resolve();
            }
        }

        typeChar();
    });
}

async function typeTextAdvanced(text, delay, targetClass, removeCursorOnEnd = false) {
    const targetEl = document.getElementById(targetClass);

    const cursorSpan = document.createElement("span");
    cursorSpan.classList.add("cursor");
    cursorSpan.textContent = "_";
    targetEl.appendChild(cursorSpan);

    for (let i = 0; i < text.length; i++) {
        cursorSpan.insertAdjacentText("beforebegin", text[i]);
        await sleep(delay);
    }

    if (removeCursorOnEnd) {
        cursorSpan.remove();
    }
}
