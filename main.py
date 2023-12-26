import pygame as pg
from prime_computing import PrimeComputing
from mapping import Mapping
from json_handler import JsonHandler


class PrimeSpiral:
    def __init__(self, screen_size, map_scale, prime_color, prime_radius,
                 key_repeat_delay=500, key_repeat_interval=50):
        self.screen_size = screen_size
        self.map_scale = map_scale
        self.prime_color = prime_color
        self.prime_radius = prime_radius

        self.json_handler = JsonHandler('primes.json')
        self.primes_list, self.prime_start = self.json_handler.read()
        self.primes_to_show = len(self.primes_list)

        self.prime_computing = PrimeComputing()
        self.mapping = Mapping(self.screen_size, self.map_scale)

        pg.key.set_repeat(key_repeat_delay, key_repeat_interval)


    def draw(self):
        # Draw the prime spiral
        # prime_start: integer
        # prime_end: integer
        # prime_thickness: integer
        # prime_radius: integer
        # prime_color: (r, g, b)
        for i in range(self.primes_to_show):
            prime = self.primes_list[i]
            point = self.mapping.rotate_vector([prime, 0], prime)
            self.mapping.draw_point(point, self.prime_color, self.prime_radius)
        

    def get_primes(self, prime_end):
        # Get all primes in the range [prime_start, prime_end]
        # prime_start: integer
        # prime_end: integer
        # primes: list of integers
        primes_list = self.prime_computing.get_primes(prime_end, self.prime_start)
        self.primes_list.extend(primes_list) if primes_list else None
        self.prime_start = prime_end if prime_end > self.prime_start else self.prime_start
        self.json_handler.write(self.primes_list, self.prime_start)


    def change_zoom(self, zoom_factor):
        # Change the zoom of the prime spiral
        # zoom_factor: float
        self.map_scale *= zoom_factor
        self.mapping.map_scale = self.map_scale

    
    def update(self):
        # Update the prime spiral
        self.mapping.screen.fill((51, 51, 51))
        self.draw()
        pg.display.flip()


if __name__ == "__main__":
    prime_spiral = PrimeSpiral(screen_size=(800, 800), map_scale=1,
                            prime_color=(0, 101, 169), prime_radius=1)
    n = 100
    prime_spiral.primes_to_show = n
    prime_spiral.get_primes(n)
    prime_spiral.update()
    while True:
        for event in pg.event.get():
            if event.type == pg.QUIT:
                pg.quit()
                exit()
            elif event.type == pg.KEYDOWN:
                if event.key == pg.K_ESCAPE:
                    pg.quit()
                elif event.key == pg.K_UP:
                    prime_spiral.change_zoom(1.1)
                    print("Zoomed in", prime_spiral.map_scale)
                elif event.key == pg.K_DOWN:
                    prime_spiral.change_zoom(0.9)
                    print("Zoomed out", prime_spiral.map_scale)
                elif event.key == pg.K_RIGHT:
                    prime_spiral.primes_to_show *= 1.25
                    prime_spiral.primes_to_show = round(prime_spiral.primes_to_show)
                    if prime_spiral.primes_to_show > len(prime_spiral.primes_list):
                        prime_spiral.get_primes(prime_spiral.primes_to_show + prime_spiral.prime_start)
                    prime_spiral.primes_to_show = min(prime_spiral.primes_to_show, len(prime_spiral.primes_list))
                    print("Showing", prime_spiral.primes_to_show, "primes")
                elif event.key == pg.K_LEFT:
                    prime_spiral.primes_to_show *= 0.75
                    prime_spiral.primes_to_show = round(prime_spiral.primes_to_show)
                    prime_spiral.primes_to_show = max(prime_spiral.primes_to_show, 0)
                    print("Showing", prime_spiral.primes_to_show, "primes")
                prime_spiral.update()
