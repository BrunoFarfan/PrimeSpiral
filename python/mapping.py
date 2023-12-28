import pygame as pg
import numpy as np


class Mapping:
    def __init__(self, screen_size, map_scale):
        self.screen_size = screen_size
        self.screen = pg.display.set_mode(self.screen_size)
        self.map_scale = map_scale
        self.map_origin = np.array(screen_size) / 2

        self.screen.fill((51, 51, 51))

        pg.init()


    def map_to_screen(self, map_point):
        # Map a point from the map coordinate system to the screen coordinate system
        # map_point: [x, y] in map coordinates
        # screen_point: [x, y] in screen coordinates
        newX = map_point[0] * self.map_scale + self.map_origin[0]
        newY = -map_point[1] * self.map_scale + self.map_origin[1]
        return np.array([newX, newY]).astype(int)
    

    def screen_to_map(self, screen_point):
        # Map a point from the screen coordinate system to the map coordinate system
        # screen_point: [x, y] in screen coordinates
        # map_point: [x, y] in map coordinates
        newX = (screen_point[0] - self.map_origin[0]) / self.map_scale
        newY = (-screen_point[1] + self.map_origin[1]) / self.map_scale
        return np.array([newX, newY])
    

    def rotate_vector(self, vector, angle):
        # Rotate a vector by a given angle
        # vector: [x, y]
        # angle: angle in radians
        # rotated_vector: [x, y]
        rotation_matrix = np.array([[np.cos(angle), -np.sin(angle)], [np.sin(angle), np.cos(angle)]])
        rotated_vector = np.dot(rotation_matrix, vector)
        return rotated_vector
    

    def draw_point(self, point, color, radius):
        # Draw a point on the screen
        # point: [x, y] in map coordinates
        # color: (r, g, b)
        # radius: radius in pixels
        screen_point = self.map_to_screen(point)
        pg.draw.circle(self.screen, color, screen_point, radius)