import React, { Component, FormEvent } from "react"
import { Option, some, none } from "fp-ts/lib/Option"
import axios from "axios"

import FriendsList, { friend } from "./FriendsList.gen"
import NewFriendForm from "./NewFriendForm"
import Loading from "./Loading"

import "./App.scss"

interface Friend_ {
  name: string
  age: number
  email: string
}

interface AppState {
  data: Option<Array<friend>>
  error: Option<string>
}

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

  addNewFriend = (friend: Friend_) => (event: FormEvent) => {
    event.preventDefault()
    axios
      .post(API_ENDPOINT, friend)
      .then(({ data }) => this.setState(() => ({ data: some(data) })))
      .catch(error => {
        this.setState({ error })
      })
  }

  render() {
    const { data } = this.state
    const JOE = {
      name: "Joe",
      age: 77,
      email: "joe@joe.joe"
    }
    return (
      <>
        {data.fold(<Loading />, data => (
          <FriendsList data={data} />
        ))}
        <NewFriendForm handleClick={this.addNewFriend(JOE)} />
      </>
    )
  }
}

export default App
