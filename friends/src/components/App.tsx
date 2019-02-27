import React, { Component } from "react"
import { Option, some, none } from "fp-ts/lib/Option"
import axios from "axios"

import "./App.scss"

interface AppState {
  data: Option<any>
}

class App extends Component<{}, AppState> {
  state = {
    data: none
  }

  componentDidMount() {
    axios
      .get("http://10.0.0.53:5000/friends")
      .then(({ data }) => this.setState(() => ({ data: some(data) })))
  }

  render() {
    const { data } = this.state
    return data.fold(<p>"Nothing to show"</p>, data => (
      <pre>{JSON.stringify(data, null, 2)}</pre>
    ))
  }
}

export default App
