document.addEventListener('DOMContentLoaded', async () => {
    await sleep(1500);
    await typeText("Visitor detected", 40, "terminal-text");
    await sleep(1000);
    await typeText("...", 300, "terminal-text");
    await sleep(1000);
    await typeText(" executing", 40, "terminal-text");
    await typeText("\u00A0greetings.exe", 40, "terminal-text-program");
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