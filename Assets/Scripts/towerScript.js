function beginPlay()
{
    timer.setTimeout(1000, shoot);
}

function shoot()
{
    engine.spawnProjectile(id);
}

function tick()
{

}

function endPlay()
{

}
//engine.spawnEnemy(id); id er entitien som dette scriptet er på.