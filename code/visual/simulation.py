import pygame
import sys
import random
import math
from pygame.locals import *

# Building board layout for bot.
SPACE = 0
GRASS = 1
WATER = 2
ROCK = 3

resources = [SPACE, GRASS, WATER, ROCK]

BROWN = (153, 76, 0)
GREEN = (0, 255, 0)
BLUE = (0, 0, 255)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)
RED = (255, 0, 0)

colors = {
	SPACE : BROWN,
	GRASS : GREEN,
	WATER : BLUE,
	ROCK : BLACK
}

# Game dimensions
TILESIZE = 32
MAPWIDTH = 20
MAPHEIGHT = 20

# tilemap = [
# 			[GRASS, ROCK, SPACE],
# 			[WATER, WATER, GRASS], 
# 			[ROCK, GRASS, WATER],
# 			[SPACE, GRASS, ROCK],
# 			[GRASS, WATER, SPACE]
# ]

# Building random map
# tilemap = [[random.choice(resources) for w in range(MAPWIDTH)] for h in range(MAPHEIGHT)]
tilemap = [[WATER if w >= 7 and w <= 12 else random.choice([SPACE, GRASS]) for w in range(MAPWIDTH)] for h in range(MAPHEIGHT)]

# Initalize the pygame module
pygame.init()

# Creates a drawing surface to display upon and captions it. 
DISPLAYSURF = pygame.display.set_mode((MAPWIDTH * TILESIZE, MAPHEIGHT * TILESIZE + 50))
pygame.display.set_caption('BattlefieldBot Simulation')

# Creating player / bot agent
PLAYER = pygame.image.load('tank.png').convert_alpha()
playerPos = [0, 0]

# Creating a basic target / enemy
TARGET = pygame.image.load('soldier.png').convert_alpha()
targetPos = [15, 15]
rescued = False
killed = False

# Creating a bomb function and object.
bomb_dict = {}
BOMB = pygame.image.load('bomb.png').convert_alpha()
EXPLOSION = pygame.image.load('nuclear.png').convert_alpha()
launched = False
detonated = False
	
# Creating statistics to track.
stats = {
	"ANGLE" : 30,
	"DIST" : 50,
	"MISSION" : "Shoot",
}

stats_icons = {
	"ANGLE" : pygame.image.load('angle.png'),
	"DIST" : pygame.image.load('distance.png'),
	"MISSION" : pygame.image.load('target.png')
}

# Creating a font for the stats.
STATFONT = pygame.font.SysFont('comicsansms', 12)

# Infinite loop to run the game. 
while True:
	# Acquire all user events. 
	for event in pygame.event.get():
		# Check for a quit intent. 
		if event.type == QUIT:
			# End game, close window
			pygame.quit()
			sys.exit()
		# Check for a key press. 
		elif event.type == KEYDOWN:
			if event.key == K_RIGHT and playerPos[0] < MAPWIDTH - 1:
				playerPos[0] += 1
			elif event.key == K_LEFT and playerPos[0] > 0:
				playerPos[0] -= 1
			elif event.key == K_DOWN and playerPos[1] < MAPHEIGHT - 1:
				playerPos[1] += 1
			elif event.key == K_UP and playerPos[1] > 0:
				playerPos[1] -= 1
			elif event.key == K_s:
				if stats["MISSION"] == "Shoot":
					stats["MISSION"] = "Rescue"
				else:
					stats["MISSION"] = "Shoot"
			elif event.key == K_SPACE:
				# Either launch a bomb or rescue the target. 
				if stats["MISSION"] == "Shoot":
					if launched:
						detonated = True
						launched = False
						killed = True
						print("BOOM!!!")
					else:
						print("Fired a bomb.")
						launched = True
						detonated = False
				else:
					if targetPos[0] == playerPos[0] and targetPos[1] == playerPos[1]:
						print("Rescued target")
						rescued = True
					else:
						print("Must be at target to rescue.")
			else:
				print("Pressed an invalid key.")

	# Draw rectangle: display to draw on, color, where to draw. 
	for row in range(0, MAPHEIGHT):
		for col in range(0, MAPWIDTH):
			pygame.draw.rect(DISPLAYSURF, colors[tilemap[row][col]], 
				(col * TILESIZE, row * TILESIZE, TILESIZE, TILESIZE))

	# Draw player. 
	DISPLAYSURF.blit(PLAYER, (playerPos[0] * TILESIZE, playerPos[1] * TILESIZE))

	# Draw target.
	if not rescued and not killed:
		DISPLAYSURF.blit(TARGET, (targetPos[0] * TILESIZE, targetPos[1] * TILESIZE))

	# Draw bomb. 
	if launched:
		DISPLAYSURF.blit(BOMB, (targetPos[0] * TILESIZE, targetPos[1] * TILESIZE))

	# Draw detonation.
	if detonated:
		DISPLAYSURF.blit(EXPLOSION, (targetPos[0] * TILESIZE, targetPos[1] * TILESIZE))

	# Display statistics.
	placePosition = 10
	for item in stats:
		DISPLAYSURF.blit(stats_icons[item], (placePosition, MAPHEIGHT * TILESIZE + 10))
		placePosition += 35
		# Calculating new angle and Euclidean distance to target. 
		if item == "ANGLE":
			adj = targetPos[1] - playerPos[1]
			hypo = math.sqrt((targetPos[1] - playerPos[1]) ** 2 + (targetPos[0] - playerPos[0]) ** 2)
			if adj == 0 or hypo == 0:
				stats[item] = 00.00
			else: 
				stats[item] = math.degrees(math.acos(adj / hypo))
				stats[item] = round(stats[item], 2)
		elif item == "DIST":
			stats[item] = math.sqrt((targetPos[1] - playerPos[1]) ** 2 + (targetPos[0] - playerPos[0]) ** 2)
			stats[item] = round(stats[item], 2)
		# else:

		textObj = STATFONT.render(str(stats[item]), True, WHITE, BLACK)
		DISPLAYSURF.blit(textObj, (placePosition, MAPHEIGHT * TILESIZE + 20))
		placePosition += 50

	# Update the display
	pygame.display.update()





