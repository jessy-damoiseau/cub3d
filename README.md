# cub3d

<img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/c/c-original.svg"  width="30" height="30" />

## Overview
 -  raycasting technique recreate a 3d game in the spirit of Wolfenstein 3D
 - The project is divided in two part : first parsing and detecting any error (such as a map not closed) within the .map passed as argument
 - Second part : render a Wolfenstein bare-bone like game based on .map config
 - Use minilibX, a graphic library derivated from OpenGL to render it visually
 - At any time, user should be able to exit either using 'exit' keypad or mouse 'x' window button
 - As usual per 42 standard : no memory leaks allowed (not even 'still reachable' type), and project is up to 42's coding norm
 - At launch, user can generate a print screen in bitmap format by adding --save after .map argument
 - Project is compatible with most linux & Mac OS recent distros
