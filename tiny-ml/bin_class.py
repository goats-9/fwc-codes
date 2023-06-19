import tensorflow as tf
from tensorflow.keras import layers
import pandas as pd

#Retrieve data
url = "https://raw.githubusercontent.com/goats-9/fwc-codes/main/tiny-ml/data/"
train_data_file = "train.csv"
test_data_file = "test.csv"

train_csv = tf.keras.utils.get_file(train_data_file, url + train_data_file)
test_csv = tf.keras.utils.get_file(test_data_file, url + test_data_file)
num_features = 180
train_dataset = pd.read_csv(train_csv)
test_dataset = pd.read_csv(test_csv)
train_input = train_dataset.loc[:, train_dataset.columns != 'target']
train_output = train_dataset.loc[:, train_dataset.columns == 'target']
test_input = test_dataset.loc[:, test_dataset.columns != 'target']
test_output = test_dataset.loc[:, test_dataset.columns != 'target']

#Define the model
model = tf.keras.Sequential([
    layers.Dense(input_shape=(num_features,)),
    layers.Dense(128, activation='relu'),
    layers.Dense(2)
])

#Compile the model
model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])

#Train the model
model.fit(train_input, train_output, epochs=10, batch_size=16)

#Evaluate the model
loss, acc = model.evaluate(test_input, test_output)

print("Accuracy:", acc)
