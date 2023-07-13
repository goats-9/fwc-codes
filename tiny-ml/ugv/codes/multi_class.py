import tensorflow as tf
from tensorflow.keras import layers
import pandas as pd
import os

num_logits = 5

#Get data
train_dataset = pd.read_csv("../data/train.csv")
test_dataset = pd.read_csv("../data/test.csv")
num_features = len(test_dataset.columns) - 1
train_input = train_dataset.iloc[:, :num_features]
train_output = train_dataset.iloc[:, num_features:num_features+1]
test_input = test_dataset.iloc[:, :num_features]
test_output = test_dataset.iloc[:, num_features:num_features+1]

#Define the model
model = tf.keras.Sequential([
    layers.Flatten(input_shape=(num_features,)),
    layers.Dense(8, activation='relu'),
    layers.Dense(num_logits)
])

#Compile the model
model.compile(optimizer='adam',
              loss=tf.keras.losses.SparseCategoricalCrossentropy(from_logits=True),
              metrics=['accuracy'])

#Train the model
model.fit(train_input, train_output, epochs=64)

#Evaluate the model
loss, acc = model.evaluate(test_input, test_output)

print("Accuracy:", acc)

converter = tf.lite.TFLiteConverter.from_keras_model(model)
converter.optimizations = [tf.lite.Optimize.DEFAULT]
tflite_model = converter.convert()

open("gesture_model.tflite", "wb").write(tflite_model)
os.system("xxd -i gesture_model.tflite > client/src/gesture_model.h")
os.system("rm gesture_model.tflite")
