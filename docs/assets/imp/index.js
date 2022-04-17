const theStoryBTN = document.getElementById("tsBtn");
const whyToUseItBTN = document.getElementById("wtuiBtn");
const waiuBTN = document.getElementById("waiuBtn");
const authBTN = document.getElementById("authBtn");

const theStory = document.getElementById("the-story");
const waiu = document.getElementById("what-api");
const htui = document.getElementById("how-to-use-it");
const auth = document.getElementById("authors");

function web()
{
    theStoryBTN.addEventListener('click', (e) =>
    {
        theStory.scrollIntoView('smooth');
    });

    whyToUseItBTN.addEventListener('click', (e) =>
    {
        waiu.scrollIntoView('smooth');
    });

    waiuBTN.addEventListener('click', (e) =>
    {
        htui.scrollIntoView('smooth');
    });

    authBTN.addEventListener('click', (e) =>
    {
        auth.scrollIntoView('smooth');
    });
}

web();