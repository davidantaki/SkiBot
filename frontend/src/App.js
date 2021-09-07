import React from 'react';
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
      <ButtonGroup>
        <Button
          text="Left"
          onMouseDown={this.handleMoveLeftEvent}
          onMouseUp={this.handleMouseUpEvent} />
        <Button
          text="Right"
          onMouseDown={this.handleMoveRightEvent}
          onMouseUp={this.handleMouseUpEvent} />
      </ButtonGroup>
    );
  }
}

export default App;