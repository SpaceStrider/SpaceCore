//------------------------------------------------------------------------------------------------
//! Returns true if character is in a vehicle
[BaseContainerProps()]
class SPC_TurretHasStabilizationCondition : SCR_AvailableActionCondition
{

	//------------------------------------------------------------------------------------------------
	//! Returns true when current controlled entity is in vehicle
	//! Returns opposite if m_bNegateCondition is enabled	
	override bool IsAvailable(SCR_AvailableActionsConditionData data)
	{
		if (!data)
			return false;

		BaconTankStuff_TurretStabilizationComponent stabilization = null;

		stabilization = CurrentTurretStabilization(data);

		if (!stabilization)
			return false;

		// Has illumination
		return GetReturnResult(true);
	}
	
	protected BaconTankStuff_TurretStabilizationComponent CurrentTurretStabilization(SCR_AvailableActionsConditionData data)
	{
		// Current vehicle controller
		BaseControllerComponent controller = data.GetCurrentVehicleController();
		if (!controller)
			return null;

		// Turret
		IEntity turretEntity = controller.GetOwner();
		if (!turretEntity)
			return null;

		// Stabilization
		return BaconTankStuff_TurretStabilizationComponent.Cast(turretEntity.FindComponent(BaconTankStuff_TurretStabilizationComponent));
	}
};
