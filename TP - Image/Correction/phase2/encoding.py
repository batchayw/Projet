from image import Image
from pixel import Pixel

class Encoder:
    def __init__(self, img: Image):
        self._image = img

    def save_to(self, path: str) -> None:
        with open(path, 'wb') as file:
            # Write ULBMP header
            file.write(b'ULBMP')  # Signature
            file.write(bytes([0x01]))  # Version 1
            header_size = 12
            file.write(header_size.to_bytes(2, 'little'))  # Header size
            file.write(self._image._width.to_bytes(2, 'little'))  # Width
            file.write(self._image._height.to_bytes(2, 'little'))  # Height
            # Write pixel data
            for pixel in self._image._pixels:
                file.write(pixel.red.to_bytes(1, 'little'))
                file.write(pixel.green.to_bytes(1, 'little'))
                file.write(pixel.blue.to_bytes(1, 'little'))


class Decoder:
    @staticmethod
    def load_from(path: str) -> Image:
        with open(path, 'rb') as file:
            # Read ULBMP header
            signature = file.read(5)
            if signature != b'ULBMP':
                raise ValueError("Invalid ULBMP file")
            version = file.read(1)
            if version != b'\x01':
                raise ValueError("Unsupported ULBMP version")
            header_size = int.from_bytes(file.read(2), 'little')
            if header_size != 12:
                raise ValueError("Incomplete ULBMP header")
            width = int.from_bytes(file.read(2), 'little')
            height = int.from_bytes(file.read(2), 'little')
            # Read pixel data
            pixels = []
            expected_pixel_bytes = width * height * 3
            pixel_data = file.read(expected_pixel_bytes)
            if len(pixel_data) != expected_pixel_bytes:
                raise ValueError("Incomplete pixel data")
            for i in range(0, expected_pixel_bytes, 3):
                red = pixel_data[i]
                green = pixel_data[i + 1]
                blue = pixel_data[i + 2]
                pixels.append(Pixel(red, green, blue))
            return Image(width, height, pixels)