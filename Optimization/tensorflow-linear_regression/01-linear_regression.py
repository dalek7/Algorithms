import tensorflow as tf
tf.set_random_seed(777)  # for reproducibility

# X and Y data
x_train = [1, 2, 3]
y_train = [1, 2, 3]

# Try to find values for W and b to compute y_data = x_data * W + b
# We know that W should be 1 and b should be 0
# But let TensorFlow figure it out
W = tf.Variable(tf.random_normal([1]), name='weight')
b = tf.Variable(tf.random_normal([1]), name='bias')

# Our hypothesis XW+b
hypothesis = x_train * W + b

# cost/loss function
cost = tf.reduce_mean(tf.square(hypothesis - y_train))

# tensorboard
cost_summ = tf.summary.scalar("cost", cost)
merged = tf.summary.merge_all()

# Minimize
optimizer = tf.train.GradientDescentOptimizer(learning_rate=0.01)
train = optimizer.minimize(cost)

# Launch the graph in a session.
sess = tf.Session()
# Initializes global variables in the graph.
sess.run(tf.global_variables_initializer())
writer = tf.summary.FileWriter("/tmp/tensorboard/linear_regression", sess.graph)


# Fit the line
for step in range(2001):
    sess.run(train)
    summary_str = sess.run(merged)
    writer.add_summary(summary_str, step)

    if step % 20 == 0:
        print(step, sess.run(cost), sess.run(W)[0], sess.run(b)[0])


# Learns best fit W:[ 1.],  b:[ 0.]

