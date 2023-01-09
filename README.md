# pimp
Pimp your images using Pietro's Image Manipulation Project (P.I.M.P)

### Disclaimer
This project is still heavily work in progress. Many features are missing and as of right now only the very bare bones of the idea are available.

## file formats
As of right now, the program only accepts 24-bit and 32-bit BITMAP images.
If you wish to convert your image to this format, you can do so very simply using ffmpeg:

`ffmpeg -i example.png example.bmp`

The reason for this is that I would like to use pure C for this project, which means no libraries that support PNG or JPEG file formats. 
This serves as a fun exercise for stuff like memory allocation, bytes, and file formats. I may decide to support more file formats in the future.

## usage
`pimp <original_file> <command> [options]`

Various commands are planned for the future, but right now here are the instructions for the ones which have been implemented:
### fill 
| argument | description | required |
|----------|-------------|:--------:|
| `first_x`  | Horizontal position of first pixel | ✅ |
| `first_y`  | Vertical position of first pixel   | ✅ |
| `last_x`   | Horizontal position of last pixel  | ✅ |
| `last_y`   | Vertical position of last pixel    | ✅ | 
| `red`      | Red value of color (0-255) (Default: 0) |  |
| `green`    | Green value of color (0-255) (Default: 0) |  |
| `blue`     | Blue value of color (0-255) (Default: 0) | |

Examples:

`pimp image.bmp fill 100 100 300 300`

Fills a square from the points (100, 100) to points (300, 300) with the default color black

`pimp image.bmp fill 200 200 600 300 255 0 255`

Fills a rectangle with the color purple (255-0-255)

## to-do
- [x] ~~read & write bmp files~~
- [x] ~~improve file structure~~
- [x] ~~fill command~~
- [ ] mirror command
- [ ] black and white command
- [ ] crop command
- [ ] blur command
- [ ] gaussian blur command
