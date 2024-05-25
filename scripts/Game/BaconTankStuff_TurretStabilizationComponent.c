class BaconTankStuff_TurretStabilizationComponentClass: ScriptGameComponentClass 
{

};

class BaconTankStuff_TurretStabilizationComponent: ScriptGameComponent 
{
	BaseCompartmentSlot m_compartment;
	TurretComponent m_turret;
	Physics m_vehiclePhysics;
	//VehicleWheeledSimulation m_VehicleWheeledSimulation;
	IEntity m_owner;
	IEntity m_parentVehicle;
	
	bool m_stabilizationOn = false;
	
	bool m_hasStabilization = true;
	
	int m_compartmentSlotId;
	
	vector m_vehicleAngles;
	vector m_turretAngles;
	
	RplComponent m_rplComponent;
	
	override void OnPostInit(IEntity owner)
		SetEventMask(owner, EntityEvent.INIT);

	override void EOnInit(IEntity owner)
	{
		if (SCR_Global.IsEditMode())
			return;
		
		//m_VehicleWheeledSimulation = VehicleWheeledSimulation.Cast(owner.FindComponent(VehicleWheeledSimulation));
		m_owner = owner;
		m_compartmentSlotId = LocateGunnerCompartment(owner);
		
		m_parentVehicle = owner.GetRootParent();
		if (m_parentVehicle)
			m_vehiclePhysics = m_parentVehicle.GetPhysics();
		
		m_turret = TurretComponent.Cast(owner.FindComponent(TurretComponent));
		
		m_rplComponent = RplComponent.Cast(owner.FindComponent(RplComponent));
		
		Print(m_parentVehicle);
		Print(m_turret);
		Print(m_owner);
		Print(m_compartmentSlotId);
		
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
		GetGame().GetInputManager().AddActionListener("TurretStabilization",EActionTrigger.DOWN,ToggleStabilization);
		
		if (!m_parentVehicle)
		{
			m_parentVehicle = m_owner.GetRootParent();
			m_vehiclePhysics = m_parentVehicle.GetPhysics();
		};
		
		m_turretAngles = m_owner.GetAngles();
		m_vehicleAngles = m_parentVehicle.GetAngles();
		
		m_owner.SetFlags(EntityFlags.ACTIVE, false);
		SetEventMask(m_owner, EntityEvent.FRAME);
	};
	
	void OnDestroyed(IEntity ent)
		Teardown();
	
	void ToggleStabilization(float value = 1, EActionTrigger reason = EActionTrigger.DOWN)
	{
		this.m_stabilizationOn = !this.m_stabilizationOn;
		Print(this.m_stabilizationOn.ToString());
	};
	
	void OnCompartmentLeft(IEntity vehicle, BaseCompartmentManagerComponent mgr, IEntity occupant, int managerId, int slotID)
	{	
		if (slotID != m_compartmentSlotId)
			return;
		
		if (occupant != SCR_PlayerController.GetLocalControlledEntity())
			return;
		
		Teardown();
	};
	
	void Teardown()
		ClearEventMask(m_owner, EntityEvent.FRAME);
	
	void OnCompartmentEntered(IEntity vehicle, BaseCompartmentManagerComponent mgr, IEntity occupant, int managerId, int slotID)
	{
		if (slotID != m_compartmentSlotId)
			return;
		
		if (occupant != SCR_PlayerController.GetLocalControlledEntity())
			return;
		
		Activate();
	};
	
	int LocateGunnerCompartment(IEntity owner)
	{
		SCR_BaseCompartmentManagerComponent compartmentManager = SCR_BaseCompartmentManagerComponent.Cast(owner.FindComponent(SCR_BaseCompartmentManagerComponent));
		if (!compartmentManager)
			return -1; 
		
		array<BaseCompartmentSlot> compartments = new array<BaseCompartmentSlot>();
		compartmentManager.GetCompartments(compartments);
		
		foreach (BaseCompartmentSlot slot : compartments)
		{
			if (slot.Type() == TurretCompartmentSlot)
				return slot.GetCompartmentSlotID();
		};
		
		return -1;
	};
	
	override void EOnFrame(IEntity owner, float timeSlice)
	{
		if (!this.m_stabilizationOn)
			return;
		
		vector rotationCurrent = m_turret.GetAimingRotation();
		
		vector currentAngles = m_parentVehicle.GetAngles();
		vector anglesChangeDelta = currentAngles - m_vehicleAngles;
		
		vector currentAnglesTurret = m_owner.GetAngles();
		vector anglesChangeDeltaTurret = currentAnglesTurret - m_turretAngles;
		
		vector rotationWant;
		
		if (Math.AbsFloat(anglesChangeDeltaTurret[0]) > 0.01)
			rotationWant[1] = anglesChangeDeltaTurret[0] * 0.8;
		
		if (Math.AbsFloat(anglesChangeDelta[1]) > 0.0001) {
			rotationWant[0] = anglesChangeDelta[1];
			rotationWant[1] = rotationWant[1] - anglesChangeDelta[2] * Math.Sin(rotationCurrent[0] * Math.DEG2RAD);
		}
		
		//rotationWant[1] = rotationWant[1] - m_vehicleAngles[2];
		
		//Print(rotationWant);
		
		
		m_turret.SetAimingRotation( (rotationCurrent - rotationWant) * Math.DEG2RAD );
		
		m_vehicleAngles = currentAngles;
		m_turretAngles = currentAnglesTurret;
	};
	
	override event protected bool OnTicksOnRemoteProxy() { return true; };
};