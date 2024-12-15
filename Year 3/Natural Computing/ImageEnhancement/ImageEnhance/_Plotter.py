import matplotlib.pyplot as plt


def sa_graph(iterations, weights):
    plt.plot(iterations, weights)
    plt.xlabel('Iteration')
    plt.ylabel('Fitness', color='b')
    plt.title('How the fitness improves over iterations of Simulated Annealing')
    plt.savefig('plots\\sa_graph.png')


def de_graph(iterations, weights):
    plt.plot(iterations, weights)
    plt.xlabel('Iteration')
    plt.ylabel('Fitness', color='b')
    plt.title('How the fitness improves over iterations of Differential Evolution')
    plt.savefig('plots\\de_graph.png')
