let transform;

function beginPlay()
{
    
}

function tick()
{
    transform = engine.getComponent("Transform", 1);

    transform.position[0] += 0.1/60;
    engine.setComponent("Transform", 1, transform);


}


function test()
{
    for(let i = 0; i < 10; i++)
    engine.printNumber(i);
}