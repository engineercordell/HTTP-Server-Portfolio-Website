document.addEventListener('DOMContentLoaded', async () => {
    await sleep(1000);
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
    let oldCursor = document.querySelector('.cursor');
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
    oldCursor = document.querySelector('.cursor');
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
});

function sleep(ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

function typeText(text, charDelay, elemID) {
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