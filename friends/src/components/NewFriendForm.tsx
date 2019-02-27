import React, { useState, FormEventHandler, ChangeEvent } from "react"
import { Friend_ } from "./App"

interface NewFriendFormProps {
  handleSubmit: (friend: Friend_) => FormEventHandler
}

interface UnvalidatedFriend {
  name: string
  age: string
  email: string
}

const validate = (friend: UnvalidatedFriend): Friend_ => ({
  ...friend,
  age: parseInt(friend.age)
})

export default ({ handleSubmit }: NewFriendFormProps) => {
  const [state, setState] = useState<UnvalidatedFriend>({
    name: "",
    age: "",
    email: ""
  })
  const handleChange = ({
    target: { value, name }
  }: ChangeEvent<HTMLInputElement>) => {
    setState(s => ({ ...s, [name]: value }))
  }
  const { name, age, email } = state
  return (
    <form onSubmit={handleSubmit(validate(state))}>
      <label>
        Name
        <input type="text" name="name" value={name} onChange={handleChange} />
      </label>
      <label>
        Age
        <input type="text" name="age" value={age} onChange={handleChange} />
      </label>
      <label>
        Email
        <input type="text" name="email" value={email} onChange={handleChange} />
      </label>
      <button>Add new friend</button>
    </form>
  )
}
