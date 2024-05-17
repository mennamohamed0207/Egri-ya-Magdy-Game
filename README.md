<div align= center >

# <img align=center width=75px height=75px src="https://media1.giphy.com/media/v1.Y2lkPTc5MGI3NjExc2pxejRtZTg5M2hveXpjcXl0bnQ3dTRmZ285ZjdpY2NoM2VzZTFrMyZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/iDCsriNfHICAlthV2q/giphy.gif"> Egri Ya Magdy


</div>


<p align="center"> 
    <br> 
</p>

## Table of Contents

- <a href ="#about"> 📙 Overview</a>
- <a href ="#started"> 💻 Get Started</a>
- <a href ="#Path"> 🎯 Path of the program</a>
- <a href ="#structure"> 📁  File Structure</a>
-  <a href ="#video"> 📽 Demo</a>
- <a href ="#contributors"> ✨ Contributors</a>
- <a href ="#license"> 🔒 License</a>
<hr style="background-color: #4b4c60"></hr>

 <a id = "about"></a>

## <img align="center"  width =70px  height =70px src="https://media1.giphy.com/media/v1.Y2lkPTc5MGI3NjExeDh5ZGd2YTZjZmJhdjE5dzZnejF6amtvdHl5Y2x3amNta2NvMmR0aCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/QTfbmaD7JZqHpmVtvT/giphy.gif"> Overview
<br>
<ul> 
<li>
Magdy tries to escape from the dog, but if he collides with the metro, the dog can catch him.</li>
<li>The game satisfies requirements:
<ul>
<li>Usage of 3D models</li>
<li>Lighting with multiple lights in the scene</li>
<li>Texture mapping</li>
<li>A sky</li>
<li>3D motion.</li>
<li>Game logic</li>
<li>Scene Deserialization</li>
<li>Scene Serialization</li>
<li>Game logic</li>
<li>Scene Deserialization</li>
<li>Play state & Menu state & Game Over state</li>
</ul>
</li>
<li>3 types of Lighting
<ul>
<li>Spot</li>
<li>Directional</li>
<li>Point</li>
</ul>
</li>
<br>
<li> Build using <a href="https://docs.gl/">OpenGl 3</a> &&<a href="https://isocpp.org/"> C++ language</a> .</li>
</ul>
<hr style="background-color: #4b4c60"></hr>
<a id = "started"></a>

## <img  align= center width=60px height=50px src="https://media2.giphy.com/media/v1.Y2lkPTc5MGI3NjExdjBxaHFnbGVjejZoNHRvMjRrM3pjNjhreDh4dGYzMGo4eWkxZzB4cCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/SYpGN9y644i496xRcG/giphy.gif"> Get Started 

<ol>
<li>Clone the repository.

<br>

```
git clone https://github.com/mennamohamed0207/Egri-ya-Magdy-Game.git
```

</li>
<li> You will need to download <a href="https://cmake.org/">CMake</a>. </li>
<br>
<li>  Install a C++ Compiler on if you haven't. Recommended (Visual Studio Community 2019 Release - amd64_x86).

<br>

```
.\bin\GAME_APPLICATION.exe\
```
</li>
</ol>
<hr style="background-color: #4b4c60"></hr>


## <img align= "center" width=80px height=80px src="https://media4.giphy.com/media/Xf8OdIAxtZqlk0PYRN/giphy.webp?cid=790b76111bs3h0dkluv3wnom89w6qcpd5o75xt8ixtxi97ap&ep=v1_gifs_search&rid=giphy.webp&ct=g"> Let's Play <a id ="Path"></a>

<ol>
<li>When run the Project</li>
<br>
<table>
<tr>
<th align="center" width=60%>Image</th>
<th width=20%>Description </th>
</tr>
<tr>
<td align="center" ><img src="https://github.com/mennamohamed0207/Egri-ya-Magdy-Game/blob/main/assets/textures/menu3.png?raw=true"></td>
<td>Main Menu you have 2 options
<ul>
<li>Click on start to start game</li>
<li>Click on quit to end game</li>
</ul>
</td>
</tr>
</table>
<li> When start Game, you can start playing.</li>
<br>
<div align="center">
<img width="500px" src="https://github.com/mennamohamed0207/Egri-ya-Magdy-Game/blob/main/assets/screenshots/Picture1.png">
</div>

<br>
<li>Settings
<ul>
<li>jump => 🔼</li>
<li>Left => ◀️</li>
<li>Right => ▶️</li>
<li>Exit Game => Esc</li>
</ul>
</li>
<li>Rules
<ul>
<li>You have at most 3 hearts. You start the game with 3 hearts.</li>
<li>If you make a collision you loss one heart and the dog will try to catch you it can't catch you as you have at least one heart.</li>
<li>when you haven't any more hearts the dog will catch you. </li>
<li>you can increase speed by taking stars.</li>
<li>Score will increase by taking coins.</li>
<li>Your goal is increasing score as you can and escape from the dog.</li>
</ul>
</li>
<li> When you die</li>
<br>
<table>
<tr>
<th align="center" width=65%>Image</th>
<th width=20%>Description </th>
</tr>
<tr>
<td align="center" ><img src="https://github.com/mennamohamed0207/Egri-ya-Magdy-Game/blob/main/assets/textures/GameOver.jpg?raw=true"></td>
<td>Game Over
<ul>
<li>Press space to start game</li>
</ul>
</td>
</tr>
</table>
</ol>
<hr style="background-color: #4b4c60"></hr>
 <a id="structure"> </a>

## <img align= center width=60px height=60px src="https://media1.giphy.com/media/igsIZv3VwIIlRIpq5G/giphy.gif?cid=ecf05e47faatmwdhcst7c2d4eontr459hjd35zf3an324elo&rid=giphy.gif&ct=s"> File Structure 
<br>
<div align= center>
<img  height="450px" src="https://github.com/BasmaElhoseny01/frog-frenzy/assets/71986226/97bd1f07-1cae-4d27-9366-4e4624015c96">
</div>
<hr style="background-color: #4b4c60"></hr>
<a id ="video"></a>

## <img  align= center width= 70px height =70px src="https://img.genial.ly/5f91608064ad990c6ee12237/bd7195a3-a8bb-494b-8a6d-af48dd4deb4b.gif?genial&1643587200063"> Demo

<div  align="center">
  <video align="center" height=300px  src="https://github.com/mennamohamed0207/Egri-ya-Magdy-Game/raw/main/assets/vedio/vedio.mp4">
</div>

> **Note**: Play the sound
<hr style="background-color: #4b4c60"></hr>
<a id ="contributors"></a>

## <img  align="center" width= 70px height =55px src="https://media0.giphy.com/media/Xy702eMOiGGPzk4Zkd/giphy.gif?cid=ecf05e475vmf48k83bvzye3w2m2xl03iyem3tkuw2krpkb7k&rid=giphy.gif&ct=s"> Contributors 

<table align="center" >
  <tr>
      <td align="center"><a href="https://github.com/SH8664"><img src="https://avatars.githubusercontent.com/u/113303945?v=4" width="150px;" alt=""/><br /><sub><b>Sara Bisheer</b></sub></a><br /></td>
      <td align="center"><a href="https://github.com/rawanMostafa08"><img src="https://avatars.githubusercontent.com/u/97397431?v=4" width="150px;" alt=""/><br /><sub><b>Rawan Mostafa</b></sub></a><br /></td>
      <td align="center"><a href="https://github.com//mennamohamed0207"><img src="https://avatars.githubusercontent.com/u/90017398?v=4" width="150px;" alt=""/><br /><sub><b>Menna Mohammed</b></sub></a><br /></td>
      <td align="center"><a href="https://github.com/fatmaebrahim"><img src="https://avatars.githubusercontent.com/u/113191710?v=4" width="150;" alt=""/><br /><sub><b>Fatma Ebrahim</b></sub></a><br /></td>
  </tr>
</table>

## 🔒 License <a id ="license"></a>

>This software is licensed under MIT License, See [License](https://github.com/BasmaElhoseny01/frog-frenzy/blob/main/LICENSE) for more information ©Frogger.