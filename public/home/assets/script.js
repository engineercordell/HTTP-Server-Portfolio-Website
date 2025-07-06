const message = "Visitor Detected...Greetings!";
let i = 0;

function type()
{
    if (i < message.length)
    {
        document.getElementById("typewriter").innerHTML += message.charAt(i);
        i++;
        setTimeout(type, 80);
    }
}

window.onload = type;