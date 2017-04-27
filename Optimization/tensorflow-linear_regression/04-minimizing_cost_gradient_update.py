# Lab 3 Minimizing Cost
import tensorflow as tf
import matplotlib.pyplot as plt
tf.set_random_seed(777)  # for reproducibility

x_data = [1, 2, 3]
y_data = [1, 2, 3]

# Try to find values for W and b to compute y_data = W * x_data + b
# We know that W should be 1 and b should be 0
# But let's use TensorFlow to figure it out
W = tf.Variable(tf.random_normal([1]), name='weight')

X = tf.placeholder(tf.float32)
Y = tf.placeholder(tf.float32)

# Our hypothesis for linear model X * W
hypothesis = X * W

# cost/loss function
cost = tf.reduce_mean(tf.square(hypothesis - Y))

# Minimize: Gradient Descent using derivative: W -= learning_rate * derivative
learning_rate = 0.1
gradient = tf.reduce_mean((W * X - Y) * X)
descent = W - learning_rate * gradient
update = W.assign(descent)

# Launch the graph in a session.
sess = tf.Session()
# Initializes global variables in the graph.
sess.run(tf.global_variables_initializer())
w_history = []
steps =[]

for step in range(21):
    sess.run(update, feed_dict={X: x_data, Y: y_data})
    curr_cost = sess.run(cost, feed_dict={X: x_data, Y: y_data})
    curr_W = sess.run(W)[0]
    w_history.append(curr_W)
    steps.append(step)
    print(step, curr_cost, curr_W)

# Show the cost function
plt.plot( steps, w_history)
plt.title('W', fontsize=10)
plt.show()