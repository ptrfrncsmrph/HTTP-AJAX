import React, { Component, FormEvent } from "react"
import { Option, some, none } from "fp-ts/lib/Option"
import axios from "axios"

import FriendsList, { friend } from "./FriendsList.gen"
import FriendForm from "./FriendForm.gen"
import Loading from "./Loading"

import "./App.scss"

export interface Friend_ {
  name: string
  age: number
  email: string
}

export interface UnvalidatedFriend_ {
  name: string
  age: string
  email: string
}

interface AppState {
  data: Option<Array<friend>>
  error: Option<string>
}

const validate = (f: UnvalidatedFriend_) => ({
  ...f,
  age: parseInt(f.age)
})

const API_ENDPOINT = "http://10.0.0.53:5000/friends"

class App extends Component<{}, AppState> {
  state = {
    data: none,
    error: none
  }

  componentDidMount() {
    axios
      .get(API_ENDPOINT)
      .then(({ data }) => this.setState(() => ({ data: some(data) })))
      .catch(error => {
        this.setState({ error })
      })
  }

  editFriend = (friend: UnvalidatedFriend_) => {
    axios
      .post(API_ENDPOINT, validate(friend))
      .then(({ data }) => this.setState(() => ({ data: some(data) })))
      .catch(error => {
        this.setState({ error })
      })
  }

  render() {
    const { data } = this.state
    return (
      <main className="App">
        {data.fold(<Loading />, data => (
          <FriendsList data={data} />
        ))}
        <FriendForm name="" age="" email="" handleSubmit={this.editFriend} />
      </main>
    )
  }
}

export default App
