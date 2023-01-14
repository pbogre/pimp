# pimp
Pimp your images using Pietro's Image Manipulation Project (P.I.M.P.)

## file formats
As of right now, the program only accepts 24-bit and 32-bit **BITMAP** images.
If you wish to convert your image to this format, you can do so very simply using ffmpeg:

`ffmpeg -i example.png example.bmp`

The reason for this is that I would like to use pure C for this project, which means no libraries that support PNG or JPEG file formats. 
This serves as a fun exercise for stuff like memory allocation, bytes, and file formats. I may decide to support more file formats in the future.

# instructions
`pimp <original_file> <command> [options]`

## pixel location guide

The `y`-value of pixels goes from top to bottom, and the `x`-value goes from left to right. To understand this, look at the table below.
| |0      |1      |
|-|-------|-------|
**0**|`(0,0)`|`(0,1)`|
**1**|`(0,1)`|`(1,1)`|

NOTE: All arguments that represent pixels positions, you are specifying the _index_ of that pixel, meaning that the position of the first pixel (top left) is `0, 0` and not `1, 1`. All you need to do to adjust to this is remove 1 from the position you have in mind.

## commands
### fill 
| argument | description | required |
|----------|-------------|:--------:|
| `first_x`  | Horizontal position of first pixel | ✅ |
| `first_y`  | Vertical position of first pixel   | ✅ |
| `last_x`   | Horizontal position of last pixel  | ✅ |
| `last_y`   | Vertical position of last pixel    | ✅ | 
| `red`      | Red value of color (0-255) (Default: 0) |❌|
| `green`    | Green value of color (0-255) (Default: 0) |❌|
| `blue`     | Blue value of color (0-255) (Default: 0) |❌|

**Examples**

`pimp image.bmp fill 100 100 300 300` Fills range (100, 100) -> (300, 300) with the default color black (0-0-0)

`pimp image.bmp fill 200 200 600 300 255 0 255` Fills range (200, 200) -> (600, 300) with the color purple (255-0-255)

---

### black and white
| argument | description | required |
|----------|-------------|:--------:|
| `first_x`  | Horizontal position of first pixel |❌|
| `first_y`  | Vertical position of first pixel   |❌|
| `last_x`   | Horizontal position of last pixel  |❌|
| `last_y`   | Vertical position of last pixel    |❌| 

**Examples**

`pimp image.bmp bw` Converts entire image to grayscale

`pimp image.bmp bw 10 30 100 130` Converts pixels in range (10, 30) -> (100, 130) to grayscale

---

### mirror
| argument | description | required |
|----------|-------------|:--------:|
| `first_x`  | Horizontal position of first pixel |❌|
| `first_y`  | Vertical position of first pixel   |❌|
| `last_x`   | Horizontal position of last pixel  |❌|
| `last_y`   | Vertical position of last pixel    |❌| 

**Examples**

`pimp image.bmp bw` Mirrors entire image

`pimp image.bmp bw 10 30 100 130` Mirrors pixels in range (10, 30) -> (100, 130)

---

### crop
| argument | description | required |
|----------|-------------|:--------:|
| `first_x`  | Horizontal position of first pixel | ✅ |
| `first_y`  | Vertical position of first pixel   | ✅ |
| `last_x`   | Horizontal position of last pixel  | ✅ |
| `last_y`   | Vertical position of last pixel    | ✅ | 

**Examples**

`pimp image.bmp crop 30 30 60 60` Crops image to pixels in range (30, 30) -> (60, 60), giving a zoom effect

---

## to-do
- [x] ~~read & write bmp files~~
- [x] ~~improve file structure~~
- [x] ~~fill command~~
- [x] ~~black and white command~~
- [x] ~~mirror command~~
- [x] ~~crop command~~
- [ ] support 24-bit w/ padding as input
- [ ] blur command
- [ ] gaussian blur command
