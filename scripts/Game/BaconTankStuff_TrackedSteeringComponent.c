class BaconTankStuff_TrackedSteeringComponentClass: ScriptComponentClass 
{

};

class BaconTankStuff_TrackedSteeringComponent: ScriptComponent 
{
	[Attribute("2", UIWidgets.Auto, "Completely arbitrary steering velocity force multiplier")]
	float m_velocityMultiplier;
	
	// Causing rubber banding due to server authority vehicles
	/*

	BaseCompartmentSlot m_compartment;
	Physics m_vehiclePhysics;
	VehicleWheeledSimulation_SA m_VehicleWheeledSimulation;
	IEntity m_owner;
	
	ref map<string, ref array<int>> m_wheels;
	
	ref array<int> m_wheelIndices = {};

	int m_compartmentSlotId;
	float m_carSteeringInput;
	float m_carSteeringClamped = 0;
	
	override void OnPostInit(IEntity owner)
		SetEventMask(owner, EntityEvent.INIT);

	override void EOnInit(IEntity owner)
	{
		m_VehicleWheeledSimulation = VehicleWheeledSimulation_SA.Cast(owner.FindComponent(VehicleWheeledSimulation_SA));
		m_owner = owner;
		m_compartmentSlotId = LocateDriverCompartment(owner);
		m_vehiclePhysics = owner.GetPhysics();
		
		SetupWheels();

		EventHandlerManagerComponent ev = EventHandlerManagerComponent.Cast(owner.FindComponent(EventHandlerManagerComponent));
		if (ev)
		{
			ev.RegisterScriptHandler("OnDestroyed", this, OnDestroyed);
			ev.RegisterScriptHandler("OnCompartmentEntered", this, OnCompartmentEntered);
			ev.RegisterScriptHandler("OnCompartmentLeft", this, OnCompartmentLeft);
		};
	};
	
	void Activate()
	{
		InputManager im = GetGame().GetInputManager();
		if (!im) return;
		
		im.AddActionListener("CarSteering", EActionTrigger.VALUE, OnCarSteeringInput);
		
		m_owner.SetFlags(EntityFlags.ACTIVE, false);
		SetEventMask(m_owner, EntityEvent.FRAME);
	};
	
	void OnCarSteeringInput(float value)
		m_carSteeringInput = value;
	
	void OnDestroyed(IEntity ent)
		Teardown();
	
	void OnCompartmentLeft(IEntity vehicle, BaseCompartmentManagerComponent mgr, IEntity occupant, int managerId, int slotID)
	{	
		if (slotID != m_compartmentSlotId)
			return;
		
		if (occupant != SCR_PlayerController.GetLocalControlledEntity())
			return;
		
		Teardown();
	};
	
	void Teardown()
	{
		ClearEventMask(m_owner, EntityEvent.FRAME);
		
		InputManager im = GetGame().GetInputManager();
		if (!im) return;
		
		im.RemoveActionListener("CarSteering", EActionTrigger.VALUE, OnCarSteeringInput);
	};
	
	void OnCompartmentEntered(IEntity vehicle, BaseCompartmentManagerComponent mgr, IEntity occupant, int managerId, int slotID)
	{
		if (slotID != m_compartmentSlotId)
			return;
		
		if (occupant != SCR_PlayerController.GetLocalControlledEntity())
			return;
		
		Activate();
	};
	
	int LocateDriverCompartment(IEntity owner)
	{
		SCR_BaseCompartmentManagerComponent compartmentManager = SCR_BaseCompartmentManagerComponent.Cast(owner.FindComponent(SCR_BaseCompartmentManagerComponent));
		if (!compartmentManager)
			return -1; 
		
		array<BaseCompartmentSlot> compartments = new array<BaseCompartmentSlot>();
		compartmentManager.GetCompartments(compartments);
		
		foreach (BaseCompartmentSlot slot : compartments)
		{
			if (slot.Type() == PilotCompartmentSlot)
				return slot.GetCompartmentSlotID();
		};
		
		return -1;
	};
	
	override void EOnFrame(IEntity owner, float timeSlice)
	{
		if (!m_VehicleWheeledSimulation.EngineIsOn())
			return;
		
		float speed = Math.Clamp(m_VehicleWheeledSimulation.GetSpeedKmh(), 0.1, 30); // above 30 km/h there is no fake steering
		float effectStrength = 1 - (speed / 30);
		
		if (!HasGroundContact())
			return;
		
		m_carSteeringClamped = Math.Clamp(m_carSteeringClamped + (-m_carSteeringInput * (timeSlice*10)), -1, 1);
		
		float gear = m_VehicleWheeledSimulation.GetGear();

		if (gear < 1)
			m_carSteeringClamped = -m_carSteeringClamped;
		
		float angularVelocityWant;
		angularVelocityWant = (m_carSteeringClamped * m_velocityMultiplier)*effectStrength;
		
		// apply some maximum to this effect 
		vector angVel = m_vehiclePhysics.GetAngularVelocity();
		angVel[1] = angVel[1] + (angularVelocityWant * (timeSlice*10));

		// do not add effect if we're spinning fast 
		if (Math.AbsFloat(angVel[1]) < 1.5)
			m_vehiclePhysics.SetAngularVelocity(angVel);
		
		// steering decay, probably not useful 
		m_carSteeringClamped = m_carSteeringClamped * (timeSlice*10);
	};
	
	bool HasGroundContact()
	{
		for (int x = 0; x < m_wheelIndices.Count(); x++)
		{
			if (m_VehicleWheeledSimulation.WheelHasContact( m_wheelIndices[x] ))
				return true;
		};
		
		return false;
	};
	
	bool SideHasContact(string side)
	{
		array<int> wheels = m_wheels.Get(side);
		
		for (int x = 0; x < wheels.Count(); x++)
		{
			if (m_VehicleWheeledSimulation.WheelHasContact( wheels[x] ))
				return true;
		};
		
		return false;
	};
	
	void SetupWheels()
	{
		for (int x = 0; x < m_VehicleWheeledSimulation.WheelCount(); x++)
		{
			m_wheelIndices.Insert(x);
		};

		Print("BaconTankStuff_TrackedSteeringComponent.SetupWheels | Wheels: "+m_wheelIndices.Count(), LogLevel.DEBUG);
	};*/
};