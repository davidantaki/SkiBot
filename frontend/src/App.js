import React from 'react';
import { Pressable, Text, View, StyleSheet } from 'react-native'
import logo from './logo.svg';
import './App.css';
import { Button, ButtonGroup } from "@blueprintjs/core";

import "@blueprintjs/core/lib/css/blueprint.css";

class App extends React.Component {
  constructor(props) {
    super(props);
    this.state = {
      btnPressed: false
    }
  }

  handleMoveLeftEvent = (event) => {
    console.log("Mouse Down");
    const options = {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify({ "moveDir": 'moveLeft' })
    }
    fetch('/move', options);
  }

  handleMoveRightEvent = (event) => {
    console.log("Mouse Down");
    const options = {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify({ "moveDir": 'moveRight' })
    }
    fetch('/move', options);
  }

  handleMouseUpEvent = (event) => {
    console.log("Mouse Up");
    const options = {
      method: 'POST',
      headers: {
        'Content-Type': 'application/json'
      },
      body: JSON.stringify({ "moveDir": 'moveStop' })
    }
    fetch('/move', options);
  }

  render() {
    return (
      <View style={styles.container}>
        <ButtonGroup>
          <Pressable
            onPressIn={this.handleMoveLeftEvent}
            onPressOut={this.handleMouseUpEvent}>
            <Button
              text="Left"
              // onMouseDown={this.handleMoveLeftEvent}
              // onMouseUp={this.handleMouseUpEvent}
              />
          </Pressable>
          <Pressable
            onPressIn={this.handleMoveRightEvent}
            onPressOut={this.handleMouseUpEvent}>
            <Button
              text="Right"
              // onMouseDown={this.handleMoveRightEvent}
              // onMouseUp={this.handleMouseUpEvent}
              />
          </Pressable>
        </ButtonGroup>
      </View>

    );
  }
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: "center",
  },
  text: {
    fontSize: 16
  },
  wrapperCustom: {
    borderRadius: 8,
    padding: 6
  },
  logBox: {
    padding: 20,
    margin: 10,
    borderWidth: StyleSheet.hairlineWidth,
    borderColor: '#f0f0f0',
    backgroundColor: '#f9f9f9'
  }
});

export default App;