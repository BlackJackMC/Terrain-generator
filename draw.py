from PIL import Image, ImageDraw

def read_terrain(height: int) -> None:
    max_height, min_height = [int(i) for i in file.readline().split(" ") if i]
    global change_rate
    change_rate = 256 / (max_height - min_height + 1)
    for _ in range(height):
        terrain.append([int(i) for i in file.readline().strip("\n").split(" ") if i])

def visualize(width: int, height: int) -> None:
    image = Image.new("RGB", (width, height), "white")
    draw = ImageDraw.Draw(image)
    for i in range(len(terrain)):
        for j in range(len(terrain[0])):
            fill_color = tuple([int(round(abs(terrain[i][j]) * change_rate)) for _ in range(3)])
            draw.rectangle([(i + 100 * i, j + 100 * j), (i + 100 + 100 * i, j + 100 + 100 * j)], fill = fill_color)

    image.show()

def main():
    global terrain, change_rate, file

    file = open("terrain.txt", "r")
    width: int = int(open("test.txt", "r").read())
    height: int = width
    for _ in range(width):    
        terrain = []
        change_rate = 0.0
        read_terrain(height)
        print(terrain)
        visualize(width * 100, height * 100)
    file.close()




if __name__ == '__main__':
    main()