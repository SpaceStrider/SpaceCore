In order to get materials to work on tracks you must add this:

 TCModFuncs {
  TCModShift "{5C709E85FA253C86}" {
   ShiftV 0.0
   Refs {
    "ShiftV" "Tank.m_RightTrack"
	}
  }
 }
 
 to any line of your material, changing the m_RightTrack variable to m_LeftTrack as needed.
 
 Example of what your material file would look like:
 
 MatPBRBasic {
 Color 0.456 0.456 0.456 1
 Cull none
 TCModFuncs {
  TCModShift "{5C709E85FA253C86}" {
   ShiftV 0.0
   Refs {
    "ShiftV" "Tank.m_LeftTrack"
	}
  }
 }
 AlphaMul 1.15
 BlendMode AlphaBlend
 RoughnessScale 2
 AOScale 0.8
 BCRMap "{9E1F386FC2366C46}Assets/Vehicles/Tracked/M270/Data/Textures/m2_bradley_tracks_flat_BCR.edds"
 OpacityMap "{1638655E9F0A338E}Assets/Vehicles/Tracked/M270/Data/Textures/m2_bradley_tracks_flat_A.edds"
 NMOMap "{A6C783FD1B413ED8}Assets/Vehicles/Tracked/M270/Data/Textures/m2_bradley_tracks_flat_NMO.edds"
}

If the tracks are moving too fast or too slow you can adjust the track speed in the tank entities parameters.