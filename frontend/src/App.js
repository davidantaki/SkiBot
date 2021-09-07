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

  handleMouseUpEvent = (event) => {
    console.log("Mouse Up");
  }

  handleMouseDownEvent = (event) => {
    console.log("Mouse Down");
  }

  render() {
    return (
      <ButtonGroup>
        <Button
          text="Left"
          onMouseDown={this.handleMouseDownEvent}
          onMouseUp={this.handleMouseUpEvent} />
        <Button
          text="Right"
          onMouseDown={this.handleMouseDownEvent}
          onMouseUp={this.handleMouseUpEvent} />
      </ButtonGroup>
    );
  }
}

export default App;