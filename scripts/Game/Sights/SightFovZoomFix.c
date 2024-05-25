// Temporally turret zoom fix
// Thank you Ram for fixing this!
modded class CharacterCameraADSVehicle
{
    protected SCR_SightsZoomFOVInfo m_SightsZoomFOVInfo;
    protected IEntity m_TurretEntity;
    protected SCR_2DSightsComponent m_Sight;

    //------------------------------------------------------------------------------------------------
    IEntity GetOwnerVehicle()
    {
        return m_OwnerVehicle;
    }

    //------------------------------------------------------------------------------------------------
    void CharacterCameraADSVehicle(CameraHandlerComponent pCameraHandler)
    {
        m_TurretEntity = m_TurretController.GetOwner();
        if (!m_TurretEntity)
            return;

        TurretComponent turret = TurretComponent.Cast(m_TurretEntity.FindComponent(TurretComponent));
        if (!turret)
            return;

        m_Sight = SCR_2DSightsComponent.Cast(turret.FindComponent(SCR_2DSightsComponent));
        if (!m_Sight)
            return;
		
        SightsFOVInfo FOVInfo = m_Sight.GetFOVInfo();
        if (!FOVInfo)
            return;

        m_SightsZoomFOVInfo = SCR_SightsZoomFOVInfo.Cast(FOVInfo);
    }

    //------------------------------------------------------------------------------------------------
    override void OnUpdate(float pDt, out ScriptedCameraItemResult pOutResult)
    {
        if (m_SightsZoomFOVInfo)
            m_SightsZoomFOVInfo.RAM_ForceUpdate(m_TurretEntity, m_Sight, pDt);

        super.OnUpdate(pDt, pOutResult);
    }
}

modded class SCR_SightsZoomFOVInfo
{
	void RAM_ForceUpdate(IEntity owner, BaseSightsComponent sights, float timeSlice)
	{
		OnUpdate(owner, sights, timeSlice);
	}
}