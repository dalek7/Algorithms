# Lab 3 Minimizing Cost
import tensorflow as tf
import matplotlib.pyplot as plt
tf.set_random_seed(777)  # for reproducibility

# tf Graph Input
X = [1, 2, 3]
Y = [1, 2, 3]

# Set wrong model weights
W = tf.Variable(-1.0)

# Linear model
hypothesis = X * W

# cost/loss function
cost = tf.reduce_mean(tf.square(hypothesis - Y))

# Minimize: Gradient Descent Magic
optimizer = tf.train.GradientDescentOptimizer(learning_rate=0.1)
train = optimizer.minimize(cost)

# Launch the graph in a session.
sess = tf.Session()
# Initializes global variables in the graph.
sess.run(tf.global_variables_initializer())

W_history = []
steps =[]


for step in range(10):
    W1 = sess.run(W)
    print(step, W1)
    W_history.append(W1)
    steps.append(step)

    sess.run(train)

linestyles = ['-', '--', '-.', ':']
# Plot
with plt.style.context(('dark_background')): # Temporary styling
    plt.plot(steps, W_history, linestyle=linestyles[1])
    plt.title('W', fontsize=10)
plt.show()