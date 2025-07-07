document.addEventListener('DOMContentLoaded', () => {
    setTimeout(startTypingAnimation, 1500, "Visitor Detected", 75);
    setTimeout(startTypingAnimation, 100, "...", 500);
    setTimeout(startTypingAnimation, 100, "Greetings!", 1000);
});

function startTypingAnimation(text, timeout) {
    const target = document.getElementById("terminal-text");
    let index = 0;

    function typeChar(timeout) {
        if (index < text.length) {
            target.textContent += text.charAt(index);
            index++;
            setTimeout(typeChar, timeout);
        }
    }

    typeChar(timeout);
}