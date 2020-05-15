let canShoot = true;
let fireRate = 250; //In msec
let radius = 2;

function beginPlay()
{
}

function tick()
{
    if(canShoot == true)
    {
        
        let npcs = engine.getAllNpcLocations();
        let transform = engine.getComponent("Transform", id);
        
        let npcsInRange = [];

        for(let i = 0; i < npcs.length; i++)
        {
            
            let distX = Math.abs((npcs[i][0] - transform.position[0]));
            let distZ = Math.abs((npcs[i][2] - transform.position[2]));

            let distance = distX * distX + distZ * distZ;

            if(distance < radius*radius)
            {
                npcsInRange.push(npcs[i]);
            }
        }
            if(npcsInRange.length != 0)
            {
                canShoot = false;
                timer.setTimeout(fireRate, resetShoot);
                engine.shoot(id, npcsInRange);
            } 
    }
}
function resetShoot()
{
    canShoot = true;
}
function endPlay()
{
}