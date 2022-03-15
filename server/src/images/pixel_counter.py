from PIL import Image
import sys
import os

dirname = os.path.dirname(__file__)
img_path = os.path.join(dirname, '../../img')
result_path = os.path.join(dirname, '../../img/tmp/result.txt')


def count_pixels(filename, pxl_value):
    cnt = 0
    img = Image.open(f'{img_path}/{filename}', 'r')
    w, h = img.size
    pixels = list(img.getdata())

    for x in range(w):
        for y in range(h):
            pxl = pixels[x+y*w]
            avg = sum(pxl)
            if avg > pxl_value:
                cnt += 1

    with open(result_path, 'w') as f:
        f.write(str(cnt))


if __name__ == "__main__":
    filename = str(sys.argv[1])
    pxl_value = int(sys.argv[2])
    count_pixels(filename, pxl_value)
    sys.exit()
