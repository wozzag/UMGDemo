
Unreal Engine 5.1.1 UMG C++ Demo

Unreal Engine 5.1.1 / Visual Studio Community 2019 / Maya 2020


All three weapons need to be picked up for the weapons UMG system.

Player controller loads the UMG assets and sets the textures and other data

Weapons and PickUps classes load their own assets

Weapons class broadcasts the overlap event 

Player character receives the event and creates weapon array

Player character calls player controller to update the UMG

PickUps classes do the same thing in a different way

UCustomButton class for the click events in MainMenu

UInfoProgressBar class for upper right progress bars and player health

UWeaponWidget class for setting weapons UMG and widget animation 

UInGameHud class for the whole UMG

