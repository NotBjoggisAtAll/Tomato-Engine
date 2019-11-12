let canShoot = true;
let fireRate = 100; //In msec

function beginPlay()
{
}



function tick()
{
    if(canShoot == true)
    {
        canShoot = false;
        console.log("hei");
        timer.setTimeout(fireRate, resetShoot);
        engine.spawnProjectile(id);
        let pos = engine.getAllNpcLocations();
        console.log(pos)
    }
}
function resetShoot()
{
    canShoot = true;
   
}
function endPlay()
{

}
//engine.spawnEnemy(id); id er entitien som dette scriptet er på.
/*
 let pos = engine.getAllNpcLocations();
    console.log(pos);
*/