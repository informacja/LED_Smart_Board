<!-- # Smart LED Board <img href="" src="https://img.shields.io/pypi/status/Django.svg"/> -->

[
 ![lsb](obj/lsb.png)
](https://drive.google.com/file/d/0B1YxDP48xFw6Vi02YWFwMk1Ba2M/view)

> *Autorzy współtworzący projekt*
> 
> Paweł Piątek - *Opiekun* · 
> Sławomir Franczyk - *Pomysłodawca* · 
> Daniel Król - *Wsparcie merytoryczne* ·
> Kasia Lachut · 
> Przemysław Kuca  · 
> Bartłomiej Mirek · 
> Dominik Kras ·
> Piotr Wawryka 

##### Osiągnięcia
[*Elektronika by żyło się łatwiej* - Politechnika Śląska](obj/ps.pdf)



##### Prototyp obsługi matrycy LED 16x16 przez Raspberry Pi 3+

<img src="./obj/1.webp" href="" alt="webp"/>

[
  ![Nagranie](./obj/vimeoMatryca.png)
](https://vimeo.com/257765594)


[
  ![pinknoise](./obj/pinknoise.gif)
](https://vimeo.com/249725802)

<img src="./obj/3.webp" href="" alt="png"/>

By Sławomir Franczyk
<img src="./obj/2.jpg" href="" alt="png"/>

<img src="./obj/clock.gif" href="" alt="gif"/>


<p><a href="./obj/soundV.mp4" download="Sound test.mp4">   Download  soundV.mp4</a><p> 

<img src="./obj/test.gif" href="" alt="gif"/>

<!-- ![lsb](obj/polsla.jpg) -->
## Audio playing response 
<img src="./obj/spectrum.gif" href="" alt="gif"/>

## Signal freq linear incrementation[time domain], spectrum looks non linear[freq domain] (ToDo: Bark Scale)
<img src="./obj/up.gif" href="" alt="gif"/>


<h2>Simple tutorial how to use command line git on RPi (configured):</h2>

```YAML
  git add . 
  git commit -m "Message eg. First Sound Test"
  git pull # download and apply changes on local repository
  git push 
```

<h2> How to configure Code::Blocks</h2>
<p><i> Project->Build options...->Linker settings</i><br>
Add to "Other linker options:"</p>

```text
-lasound
-lpthread
-lncurses 
```

<img src="./obj/conf_codeblocks.png" href="" alt="CodeBlocs Configuration"/>

<p>And in <i>Project->Build options...->Search directories </i><br> 
Add to "Compiler" </p>

```text
include
```


