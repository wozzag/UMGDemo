WIP UE5.2 UMG C++


** Pickup all 3 Weapons first before picking up ammo or health **

** Mouse right click to switch weapons **

** Meshes modelled in Maya **



PlayerController creates the widgets and adds to the viewport.

MainMenu loads textures and sets the images and button style.

InGameHud loads textures and sets up the HUD.

InGameHud uses WeaponWidget Class and InfoProgressBar class and sets the data and animations.

Ammo pickup classes set the data of the current and max ammo of PlayerCharacter's' weapons and
updates the WeaponWidget text through PlayerController->InGameHUDInstance.

Weapon overlap broadcasts to PlayerCharacter and adds the weapon to array.

PlayerCharacter calls PlayerController->InGameHUDInstance to show the corresponding widget.
