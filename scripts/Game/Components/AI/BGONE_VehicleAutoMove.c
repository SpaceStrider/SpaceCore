class BGONE_VehicleAutoMoveComponentClass : ScriptComponentClass
{
};

class BGONE_VehicleAutoMoveComponent : ScriptComponent
{ /*
	override void EOnInit(IEntity owner)
	{
		BaseVehicle veh = BaseVehicle.Cast(owner);
		SCR_CarControllerComponent_SA cont = SCR_CarControllerComponent_SA.Cast(veh.FindComponent(SCR_CarControllerComponent_SA));
		VehicleWheeledSimulation_SA sim = cont.GetWheeledSimulation();
		if(!sim)
		{
			Print("BGONE - VehicleMover Cant Find VehicleWheeledSimulation_SA On Entity",LogLevel.WARNING);
			return;
		}
		sim.EngineStart();
		sim.SetBreak(0,false);
		sim.SetThrottle(1);
		sim.SetGear(2);
		sim.SetClutch(1);
		
		sim.ForceEnableSimulation();
	}
	
	override void OnPostInit(IEntity owner)
	{
		SetEventMask(owner, EntityEvent.INIT);
	} */
}