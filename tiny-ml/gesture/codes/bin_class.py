import tensorflow as tf
from tensorflow.keras import layers
import pandas as pd
import os

#Get data
train_dataset = pd.read_csv("../data/train.csv")
test_dataset = pd.read_csv("../data/test.csv")
train_input = train_dataset.loc[:, train_dataset.columns != 'target']
train_output = train_dataset.loc[:, train_dataset.columns == 'target']
test_input = test_dataset.loc[:, test_dataset.columns != 'target']
test_output = test_dataset.loc[:, test_dataset.columns == 'target']
num_features = len(test_dataset.columns) - 1

#Define the model
model = tf.keras.Sequential([
    layers.Flatten(input_shape=(num_features,)),
    layers.Dense(1, activation='sigmoid')
])

#Compile the model
model.compile(loss='binary_crossentropy', optimizer='adam', metrics=['accuracy'])

#Train the model
model.fit(train_input, train_output, epochs=32)

#Evaluate the model
loss, acc = model.evaluate(test_input, test_output)

print("Accuracy:", acc)

converter = tf.lite.TFLiteConverter.from_keras_model(model)
converter.optimizations = [tf.lite.Optimize.DEFAULT]
tflite_model = converter.convert()

open("gesture_model.tflite", "wb").write(tflite_model)
os.system("xxd -i gesture_model.tflite > client/src/gesture_model.h")
os.system("rm gesture_model.tflite")
