let i = 0;
const minTime = 800;
const maxTime = 1200;
let randomSpawnTime = getRndInteger(minTime, maxTime);

function beginPlay()
{
}

function getRndInteger(min, max)
{
    return Math.floor(Math.random() * (max - min) ) + min;
}

function tick()
{
    i += (1/60) * 1000;

    if(i > randomSpawnTime)
    {
        engine.spawnEnemy(id);
        i = 0;
        randomSpawnTime = getRndInteger(minTime,maxTime);
    }
}

function endPlay()
{
}