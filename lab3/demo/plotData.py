import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib.animation import FuncAnimation

def read_particle_positions(file_path):
    # Liste pour stocker les positions des particules
    positions_per_time = {}
    speed_per_time = {}
    time = 1

    # Ouvrir le fichier et lire ligne par ligne
    with open(file_path, 'r') as file:
        time_step_positions = []
        time_step_speed = []
        for line in file:
            # Ignorer les lignes vides (changement de temps)
            if not line.strip():
                if time_step_positions:
                    positions_per_time[time] = time_step_positions
                    speed_per_time[time] = time_step_speed
                time_step_positions = []
                time_step_speed = []
                time += 1
            else:
                # Extraire les coordonnées X, Y, Z de chaque particule
                coords = list(map(float, line.split()))
                time_step_positions.append(coords[:3])
                time_step_speed.append(coords[3:])

        # Ajouter la dernière étape de temps
        if time_step_positions:
            positions_per_time[time] = time_step_positions
            speed_per_time[time] = time_step_speed

    return positions_per_time, speed_per_time

def update_plot(frame, positions_per_time, speed_per_time, scat, ax, quiver_list):
    # Récupérer les positions des particules pour l'instant de temps "frame"
    positions = positions_per_time[frame + 1]
    x_vals = [pos[0] for pos in positions]  # X
    y_vals = [pos[1] for pos in positions]  # Y
    z_vals = [pos[2] for pos in positions]  # Z

    speed = speed_per_time[frame + 1]
    x_speed = [pos[0] for pos in speed]  # X
    y_speed = [pos[1] for pos in speed]  # Y
    z_speed = [pos[2] for pos in speed]  # Z

    # Mettre à jour les coordonnées des particules sur le graphique
    scat._offsets3d = (x_vals, y_vals, z_vals)

    # Supprimer les anciens vecteurs de vitesse
    for quiver in quiver_list:
        quiver.remove()
    quiver_list.clear()

    # Dessiner les nouveaux vecteurs de vitesse
    quiver = ax.quiver(x_vals, y_vals, z_vals, x_speed, y_speed, z_speed, length=0.1, normalize=True, color='r')
    quiver_list.append(quiver)

    # # Ajuster dynamiquement les limites des axes
    # ax.set_xlim(min(x_vals), max(x_vals))
    # ax.set_ylim(min(y_vals), max(y_vals))
    # ax.set_zlim(min(z_vals), max(z_vals))

    return scat,

def plot_particle_positions(positions_per_time, speed_per_time):
    # Créer un graphique en 3D
    fig = plt.figure()
    ax = fig.add_subplot(111, projection='3d')

    # Initialiser les coordonnées pour la première étape de temps
    first_positions = positions_per_time[1]
    x_vals = [pos[0] for pos in first_positions]
    y_vals = [pos[1] for pos in first_positions]
    z_vals = [pos[2] for pos in first_positions]

    first_speed = speed_per_time[1]
    x_speed = [pos[0] for pos in first_speed]
    y_speed = [pos[1] for pos in first_speed]
    z_speed = [pos[2] for pos in first_speed]

    # Créer le graphique de dispersion pour les particules
    scat = ax.scatter(x_vals, y_vals, z_vals)

    # Créer les vecteurs vitesse normés
    quiver_list = []  # Liste pour stocker les objets quiver
    quiver = ax.quiver(x_vals, y_vals, z_vals, x_speed, y_speed, z_speed, length=0.1, normalize=True, color='r')
    quiver_list.append(quiver)

    # # Définir les limites initiales des axes
    # ax.set_xlim(min(x_vals), max(x_vals))
    # ax.set_ylim(min(y_vals), max(y_vals))
    # ax.set_zlim(min(z_vals), max(z_vals))

    # Créer l'animation pour mettre à jour les positions des particules et les vecteurs vitesse
    anim = FuncAnimation(fig, update_plot, frames=len(positions_per_time) - 1,
                         fargs=(positions_per_time, speed_per_time, scat, ax, quiver_list), interval=100)

    # Afficher l'animation
    plt.show()

# Exemple d'utilisation
file_path = '/user/8/audigiem/2A/S8/cpp/lab3/demo/dataSimulation.txt'
positions_per_time, speed_per_time = read_particle_positions(file_path)

# Afficher l'animation des positions des particules
plot_particle_positions(positions_per_time, speed_per_time)